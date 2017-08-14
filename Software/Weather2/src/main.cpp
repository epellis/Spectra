#include <Arduino.h>

#include <WiFiManager.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

#include <ArduinoJson.h>

void startupWiFi();
void updateLocation();
void updateWeather();
String buildHTTPRequest(String host, String url);
String buildHTTPSRequest(String host, String url);

String latitude = "";
String longitude = "";
String temperature = "";

void setup()
{
  Serial.begin(115200);
  startupWiFi();
  updateLocation();
  updateWeather();

  float temp = temperature.toFloat();

  Serial.print("The max temperature is: ");
  Serial.println(temp);
}

void loop() {}

/* This function sets up the device as a WiFi station using ssid and password
 * credentials. Also will print debug statements to serial.
*/
void startupWiFi()
{
  // const char *ssid = "belkin.6ca";
  // const char *password = "3a4ef399";

  const char *ssid = "IllinoisNet_Guest";
  const char *password = "";

  // Connect to WiFi Network
  WiFi.begin(ssid, password);
  Serial.println("Connecting to network");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.println("Connected to network.");
}

/* Updates latitude and longitude to the approximate coordinates of the device
 * This is done by sending an HTTP request to ip-api and parsing the returned
 * JSON file.
*/
void updateLocation()
{
  String host = "ip-api.com";
  String url = "json";
  String response = "";

  // Setup a client instance with the given host
  WiFiClient client;
  if (client.connect("ip-api.com", 80)) {
    Serial.println("Connected to host");
  } else {
    Serial.println("Could not connect to host");
  }

  // HTTP Get request for the given url
  String httpRequest = buildHTTPRequest(host, url);
  Serial.print(httpRequest);
  client.print(httpRequest);

  // Parse each line recieved and see if it is in JSON format
  while (client.connected()) {
    if (client.available()) {
      String line = client.readStringUntil('\n');
      if (line.startsWith("{")) response = line;
    }
  }
  client.stop();

  // Parse the string into a JSON buffer for easy refrencing
  DynamicJsonBuffer jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(response);

  String lat = root["lat"];
  String lon = root["lon"];

  latitude = lat;
  longitude = lon;

  String exitMessage = "Coordinates " + lat + " , " + lon;
  Serial.println(exitMessage);
}

void updateWeather()
{
  String apiKey = "09fc2d17293f5550892338ce88a4a4c4";
  String host = "api.darksky.net";
  String url = "forecast/";
  String response = "";

  // Build the final url and request string
  url = url + apiKey + "/" + latitude + "," + longitude;
  String httpsRequest = buildHTTPSRequest(host, url);

  // Setup an instance of secure client
  WiFiClientSecure client;
  if (client.connect("darksky.net", 443)) {
    Serial.println("Connected to host darksky");
  } else {
    Serial.println("Could not connect to host");
  }

  // Connect and parse json
  client.print(httpsRequest);
  Serial.println(httpsRequest);

  int daily_flag = 0;

  while (client.connected() || client.available()) {
    String line = client.readStringUntil(',');

    // Search for the "daily" tag in JSON
    if (line.startsWith("\"daily\"")) daily_flag = 1;

    if (daily_flag && line.startsWith("\"temperatureMax\"")) {
      int start_index = line.indexOf(":");
      temperature = line.substring(start_index + 1);
      daily_flag = 0;
    }

  }
  client.stop();

  Serial.print(response);
  Serial.println("Weather Updated.");
}

String buildHTTPRequest(String host, String url)
{
  return String("GET /") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n";
}

String buildHTTPSRequest(String host, String url)
{
  return String("GET /") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n";
}
