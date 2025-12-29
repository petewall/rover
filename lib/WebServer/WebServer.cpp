#include "WebServer.h"

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <stdlib.h>

#include "LED.h"
#include "hardware.h"

namespace {

bool parseStateParam(const String& value) {
  String normalized = value;
  normalized.toLowerCase();
  return normalized == "1" || normalized == "true" || normalized == "on";
}

String buildStatePayload(bool state) {
  return String("{\"state\":") + (state ? "true" : "false") + "}";
}

}  // namespace

WebServer::WebServer(LED* led)
    : asyncWebServer(nullptr), led(led) {
  asyncWebServer = new AsyncWebServer(80);
  // Mount LittleFS and serve static files from it (default to index.html)
#if defined(ESP8266)
  if (!LittleFS.begin()) {
    Serial.println("LittleFS mount failed");
  } else {
    Serial.println("LittleFS mounted");
  }
#elif defined(ESP32)
  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS mount failed");
  } else {
    Serial.println("LittleFS mounted");
  }
#endif

  asyncWebServer->serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
  asyncWebServer->on(
      "/led", HTTP_GET, [this](AsyncWebServerRequest* request) {
        if (request->hasParam("state")) {
          const String value = request->getParam("state")->value();
          this->led->setState(parseStateParam(value));
        }
        request->send(200, "application/json",
                      buildStatePayload(this->led->getState()));
      });

  asyncWebServer->begin();
  Serial.println("HTTP server started");
}
