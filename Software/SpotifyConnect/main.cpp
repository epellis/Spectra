#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

void connectToWiFi();
void authenticateWithSpotify();
void getTrackInformation();
void visualizeTrack();

void setup()
{

}

void loop() {}

void connectToWiFi()
{
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
}

void authenticateWithSpotify()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("DNSServer CaptivePortal Example");

  dnsServer.start(DNS_PORT, "*", apIP);

  webServer.onNotFound([](){
    webServer.send(200, "text/html", "<!DOCTYPE html><html><h1>Hello World</h1></html>");
  })
  webServer.begin();
}
