#include <ESP8266WiFi.h>

const char* ssid = "IllinoisNet_Guest";
const char* pass = "";

const char* string_latitude = "37.8267";
const char* string_longitude = "-122.4233";

const char* DARKSKY_HOST = "api.darksky.net";
const char* DARKSKY_SITE = "/forecast/";
const char* DARKSKY_KEY = "09fc2d17293f5550892338ce88a4a4c4";
String payload;

const int httpsPort = 443;
const char* fingerprint = "09 06 57 20 F0 85 0A 63 15 4E 68 81 6D 1F 49 E8";

void connectWiFi() {
  /* Connect to provided WiFi */
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  connectWiFi();
  
  char dark_sky_site[80];
  strcpy(dark_sky_site, DARKSKY_SITE);
  strcat(dark_sky_site, DARKSKY_KEY);
  strcat(dark_sky_site, "/");
  strcat(dark_sky_site, string_latitude);
  strcat(dark_sky_site, ",");
  strcat(dark_sky_site, string_longitude);
  Serial.print("Site Host: ");
  Serial.println(DARKSKY_HOST);
  Serial.print("Site: ");
  Serial.println(dark_sky_site);
  WiFiClientSecure https_client;
  int connect_status = https_client.connect(DARKSKY_HOST, httpsPort);
  if (connect_status) {
    Serial.println("Connection good!");
  }
  https_client.print(String("GET ") + dark_sky_site + " HTTP/1.1\r\n" +
               "Host: " + DARKSKY_HOST + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Accept-Language: en-US,en;q=0.5" +
               "Accept-Encoding: gzip, deflate, br" +
               "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8" +
               "Connection: keep-alive\r\n\r\n");
  while (https_client.connected()) {
    if (https_client.available()) {
      String line = https_client.read();
      Serial.println(line);
    }
  }
}
void loop() {
  delay(100);
}
