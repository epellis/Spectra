/* **************** LIBRARY DECLARATIONS **************** */

#include <ArduinoJson.h>    // JSON parsing library for C++
#include <ESP8266WiFi.h>    // ESP8266 WiFi library
#include <ESP8266HTTPClient.h>    // ESP8266 HTTP request library
#include "FastLED.h"    // WS2812B Pixel Driver
#include <Math.h>   // Math functions library

/* **************** CONSTANT DECLARATIONS **************** */

/* WiFi Authentication */
const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";

/* Weather API Authentication */
const char* DARKSKY_HOST = "";
const char* DARKSKY_USER = "";
const char* DARKSKY_KEY = "";
String temperature;
String humidity;
String wind_speed;
String wind_bearing;

/* Free GeoIP API Authentication */
const char* IPINFO_HOST = "freegeoip.net/json/";
String longitude;   // North-South Coordinate
String latitude;   // East-West Coordinate

/* Climate maxes and mins, used to accurately scale weather data*/
const float TEMP_RANGE 100;
const float WIND_RANGE 40;

/* Board information */
const int DISPLAY_SIZE 8;
const int ARRAY_SIZE 64;

/* **************** STRUCT DECLARATIONS **************** */

struct pix {
  unsigned int isWindy:1;
  int bg_red;
  int bg_green;
  int bg_blue;
  float exact_x_pos;
  float exact_y_pos;
  float period;
  float phase;
}

/* **************** FUNCTION DECLARATIONS **************** */

void getCoordinates() {
  HTTPClient http;    // Create new instance of HTTPClient object
  http.begin(IPINFO_HOST);    // Connect to website defined above
  if (http.GET() > 0) {   // If the server responds, continue
    char response[] = http.getString();   // Store the response for the website as a string
    StaticJsonBuffer<500> jsonBuffer;   // Set up a new JsonBuffer of size 500
    JsonObject& IPInfoResponse = jsonBuffer.parseObject(response);    // Parse string as json
    longitude = IPInfoResponse["longitude"];    // Copy parsed field into string
    latitude = IPInfoResponse["latitude"];    // Copy parsed field into string
  }
  http.end();
}

void getWeather(char* device_longitude, char* device_latitude) {
  HTTPClient http;

  /* To create the full link we need to concat several strings */
  char dark_sky_site[80];
  strcpy(dark_sky_site, DARKSKY_HOST);
  strcat(dark_sky_site, DARKSKY_KEY);
  strcat(dark_sky_site, device_longitude);
  strcat(dark_sky_site, device_latitude);

  http.begin(dark_sky_site);
  if (http.GET() > 0) {
    char response[] = http.getString();
    StaticJsonBuffer<500> jsonBuffer;   // Set up a new JsonBuffer of size 500
    JsonObject& DARKSKY_RESPONSE = jsonBuffer.parseObject(response);    // Parse string as json
    temperature = DARKSKY_RESPONSE["temperature"];
    humidity = DARKSKY_RESPONSE["humidity"];
    wind_speed = DARKSKY_RESPONSE["windSpeed"];
    wind_bearing = DARKSKY_RESPONSE["windBearing"];
  }
}

void updateInfo() {
  /* Connect to WiFi */
  WiFi.mode(WIFI_STA);    // Set mode to client
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);   // Loop until connected
  }

  getCoordinates();
  getWeather();
}

void spawnWindy(int index) {

}

int transferFX(struct pix* passed_pix, float x_velocity, float y_velocity) {
  /* Apply velocity timestep */
  float next_x = passed_pix.exact_x_pos + x_velocity;
  float next_y = passed_pix.exact_y_pos + y_velocity;

  /* "Killed" State */
  if (next_x < 0 || next_x > DISPLAY_SIZE - 1 || next_y < 0 || next_y > DISPLAY_SIZE - 1) {
    passed_pix.isWindy = 0;
    return 1;
  }

  /* Transfer pixel to another */
  else if (next_x != passed_pix.exact_x_pos || next_y != passed_pix.exact_y_pos) {
    matrix[next_x].isWindy = 1;
    matrix[next_x].exact_x_pos = next_x;
    matrix[next_x].exact_y_pos = next_y;
    passed_pix.isWindy = 0;
    return 0;
  }

  /* Keep same pixel */
  else {
    passed_pix.exact_x_pos = next_x;
    passed_pix.exact_y_pos = next_y;
    return 0;
  }
}

// returns 1 if failed
void oscillateFX(struct pix* passed_pix) {
  int multiplier = 1 * sin16(passed_pix.phase + period);
  passed_pix.phase++;
  if (passed_pix.phase > 255) { passed_pix.phase = 0; }
}

void prepareWeather() {
  /* First, we get our x and y components of wind speed vector */
  float x_velocity = wind_speed * sin(wind_speed);
  float y_velocity = wind_speed * cos(wind_speed);
  float pix_temperature = temperature % 256;

  /* Now scale for min/max of climate */
  x_velocity *= (1 / WIND_RANGE);
  y_velocity *= (1 / WIND_RANGE);

  /* Set a max number of Windy Particles based on humidity */
  int max_windy = humidity / 10;
  int current_windy = 0;

  /* Declare an array of pix objects */
  struct matrix pix[ARRAY_SIZE];

  /* Initialize each pixel */
  for (int i = 0; i < ARRAY_SIZE; i++) {
    matrix[i].isWindy = 0;
    matrix[i].bg_red = pix_temperature;
    matrix[i].bg_blue = 256 - pix_temperature;
    matrix[i].bg_green = matrix[i].bg_red * 0.25 + matrix[i].bg_blue * 0.75;
    matrix[i].windy_red = matrix[i].bg_red * 4;
    matrix[i].windy_green = matrix[i].bg_green * 4;
    matrix[i].windy_blue = matrix[i].bg_blue * 4;
    matrix[i].period = random16() % 64;
    matrix[i].phase = random16() % 64;
  }

  renderWeather(*matrix);
}

void renderWeather(struct* pix matrix) {
 /*
  * PASS I
  *   Spawn new windy particles if current_windy < max_windy
  *   Calculate the new position of the pixels
  *   If position is a new LED, transfer pixel data
  *   If position is out of bounds, kill pixel, decrement current_windy
  */

  /* Spawn new pixels */
  while (current_windy < max_windy) {
    int random_index = random16() % (ARRAY_SIZE);
    spawnWindy(random_index);
  }

  /* Iterate through array to find all windy particles */
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (matrix[i].isWindy) {
      int status = transferFX(matrix[i]);
      current_windy -= status;    // So if the function returns a 1 meaning it failed, decrement the windy particle counter
    }
  }

 /*
  * PASS II
  *   If the pixel is not windy
  *   Continue to oscillate color based on data
  */
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (!matrix[i].isWindy) {
      // osciallting color shift
      oscillateFX(matrix[i]);
    }
  }

  // render to screen

}

void setup() {
  updateInfo();
}

void loop() {
}
