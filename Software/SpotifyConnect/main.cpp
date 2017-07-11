#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

void connectToWiFi();
void authenticateWithSpotify();
void getTrackInformation();
void visualizeTrack();

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

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
  WiFi.softAP("Spectra Access Point");

  dnsServer.start(DNS_PORT, "*", apIP);

  webServer.onNotFound([](){
    webServer.send(200, "text/plain", "Hello World!");
  })
  webServer.begin();
}
