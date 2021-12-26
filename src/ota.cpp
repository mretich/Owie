#include <AsyncElegantOTA.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define SSID_NAME "BMS OTA"

namespace {
// Init System Settings
DNSServer dnsServer;
AsyncWebServer webServer(80);

}  // namespace

void ota_setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP("BMS OTA");
  dnsServer.start(53, "*", WiFi.softAPIP());  // DNS spoofing (Only HTTP)
  webServer.onNotFound([&](AsyncWebServerRequest *request) {
    request->redirect("http://" + WiFi.softAPIP().toString() + "/update");
  });
  AsyncElegantOTA.begin(&webServer);
  webServer.begin();
}

void ota_loop() { dnsServer.processNextRequest(); }