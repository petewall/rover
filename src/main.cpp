// System dependencies
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266mDNS.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <ESPmDNS.h>
#endif

// External libraries

// Internal libraries
#include "hardware.h"
#include "LED.h"
#include "WebServer.h"

WebServer* webServer;

#define BLINK_DELAY_MS 500

bool ledState = false;
LED *led;

void connectToWiFi(void) {
  WiFi.mode(WIFI_STA);
  #ifdef HOSTNAME
    #if defined(ESP8266)
      WiFi.hostname(HOSTNAME);
    #elif defined(ESP32)
      WiFi.setHostname(HOSTNAME);
    #endif
  #endif
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  #if (defined(ESP8266) || defined(ESP32)) && defined(HOSTNAME)
    if (!MDNS.begin(HOSTNAME)) {
      Serial.println("Error setting up mDNS responder");
    } else {
      Serial.print("mDNS responder started: ");
      Serial.print(HOSTNAME);
      Serial.println(".local");
      MDNS.addService("http", "tcp", 80);
    }
  #endif
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);  // Ensure LED is off on boot (active low)

  Serial.begin(115200);
  Serial.println();
  Serial.println("Rover firmware booting...");

  led = new LED(RGB_LED_PIN);

  connectToWiFi();
  webServer = new WebServer(led);
}

void loop() {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState ? LOW : HIGH);
  delay(BLINK_DELAY_MS);
}
