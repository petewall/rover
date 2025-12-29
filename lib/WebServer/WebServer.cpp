#include "WebServer.h"

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <stdlib.h>

#include "LED.h"
#include "hardware.h"

namespace {

uint8_t clampColorComponent(const String& value) {
  long parsed = value.toInt();
  if (parsed < 0) {
    parsed = 0;
  } else if (parsed > 255) {
    parsed = 255;
  }
  return static_cast<uint8_t>(parsed);
}

String buildColorPayload(uint8_t r, uint8_t g, uint8_t b) {
  String payload = "{\"r\":";
  payload += r;
  payload += ",\"g\":";
  payload += g;
  payload += ",\"b\":";
  payload += b;
  payload += "}";
  return payload;
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
        uint8_t r = this->led->getRed();
        uint8_t g = this->led->getGreen();
        uint8_t b = this->led->getBlue();
        bool updated = false;

        if (request->hasParam("r")) {
          r = clampColorComponent(request->getParam("r")->value());
          updated = true;
        }
        if (request->hasParam("g")) {
          g = clampColorComponent(request->getParam("g")->value());
          updated = true;
        }
        if (request->hasParam("b")) {
          b = clampColorComponent(request->getParam("b")->value());
          updated = true;
        }

        if (updated) {
          this->led->setColor(r, g, b);
        }
        request->send(200, "application/json",
                      buildColorPayload(this->led->getRed(),
                                        this->led->getGreen(),
                                        this->led->getBlue()));
      });

  asyncWebServer->begin();
  Serial.println("HTTP server started");
}
