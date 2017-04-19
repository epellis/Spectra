#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>    // JSON parsing library for C++

const char* IPINFO_HOST = "http://freegeoip.net/json/";

const char* ssid = "IllinoisNet_Guest";
const char* pass = "";
String payload;
const char* string_latitude;
const char* string_longitude;
/* Weather API Authentication */
const char* DARKSKY_HOST = "https://api.darksky.net/forecast/";
const char* DARKSKY_KEY = "09fc2d17293f5550892338ce88a4a4c4";
//const char* temperature;
//const char* humidity;
//const char* wind_speed;
//const char* wind_bearing;

void setup() {
  Serial.begin(115200);

  /* Code to get the MAC Address */
  //  uint8_t macAddr[6];
  //  WiFi.macAddress(macAddr);
  //  Serial.print("Connected to: ");
  //  for (int i = 0; i < 6; i++) {
  //    Serial.printf("%02x:", macAddr[i]);
  //  }
  //  Serial.println();

  /* Connect to provided WiFi */
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");

  /* Setup HTTPS Connection */
  HTTPClient http;
  http.begin(IPINFO_HOST);
  int httpCode = http.GET();
  if (httpCode > 0) {
    payload = http.getString();
  }
  else {
  }
  http.end();

  /* Parse the passed string */
  StaticJsonBuffer<500> jsonBuffer;   // Set up a new JsonBuffer of size 500
  JsonObject& IP_RESPONSE = jsonBuffer.parseObject(payload);    // Parse string as json
  string_longitude = IP_RESPONSE["longitude"];
  string_latitude = IP_RESPONSE["latitude"];

//  Serial.println(longitude);
//  Serial.println(latitude);

//  longitude = atof(string_longitude);
//  latitude = atof(string_latitude);

  delay(1000);

  Serial.printf("Device is currently at position: %s,%s\n", string_latitude, string_longitude);

  /* Get weather information from dark sky API */
  /* To create the full link we need to concat several strings */
  char dark_sky_site[80];
  strcpy(dark_sky_site, DARKSKY_HOST);
  strcat(dark_sky_site, DARKSKY_KEY);
  strcat(dark_sky_site, "/");
  strcat(dark_sky_site, string_latitude);
  strcat(dark_sky_site, ",");
  strcat(dark_sky_site, string_longitude);
  

  delay(1000);
  Serial.printf("Sending get request to site: %s\n", dark_sky_site);

  http.begin(dark_sky_site);
  httpCode = http.GET();
  Serial.println(httpCode);
  if (httpCode > 0) {
    payload = http.getString();

    const size_t bufferSize = JSON_ARRAY_SIZE(2) + JSON_ARRAY_SIZE(4) + JSON_ARRAY_SIZE(8) + JSON_ARRAY_SIZE(49) + 3*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(8) + 50*JSON_OBJECT_SIZE(14) + 6*JSON_OBJECT_SIZE(22) + JSON_OBJECT_SIZE(24) + JSON_OBJECT_SIZE(25) + 18270;
    StaticJsonBuffer<500> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(payload);
    JsonObject& currently = root["currently"];

    const char* test_phrase = "Hello World";
    const char* temperature = currently["temperature"];
    const char* humidity = currently["humidity"];
    const char* wind_speed = currently["windSpeed"];
    const char* wind_bearing = currently["windBearing"];

    delay(1000);

    printf("Test Case: %s\n", test_phrase);
    Serial.println(payload);
    printf("Temperature: %s\n", temperature);
    printf("Humidity: %s\n", humidity);
    printf("Wind Speed: %s\n", wind_speed);
    printf("Wind Bearing: %s\n", wind_bearing);
  }
  
  http.end();
}

void loop() {
  delay(1000);
}
