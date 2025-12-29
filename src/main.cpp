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
#include "Battery.h"
#include "LED.h"
#include "WebServer.h"

WebServer* webServer;

#define BLINK_DELAY_MS 250
#define READY_DELAY_MS 500
#define BATTERY_LOG_INTERVAL_MS 5000

bool ledState = false;
bool ready = false;
bool reportedReady = false;
LED* led = nullptr;
Battery* battery = nullptr;
unsigned long lastBatteryLog = 0;

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
}

void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    ready = false;
    reportedReady = false;
    Serial.print(".");
    return;
  }
  if (!ready) {
    ready = true;
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
      Serial.println(".localdomain");
      MDNS.addService("http", "tcp", 80);
    }
#endif
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);  // Ensure LED is off on boot (active low)

  led = new LED(RGB_LED_PIN);
  led->begin();
  led->off();

  battery = new Battery(BATTERY_ADC_PIN);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Rover firmware booting...");

  connectToWiFi();
  webServer = new WebServer(led, battery);
}

void loop() {
  ledState = !ledState;
  checkWiFiConnection();
  if (!ready) {
    ledState ? led->red() : led->off();
  } else if (!reportedReady && ledState) {
    led->green();
    delay(READY_DELAY_MS);
    led->off();
    reportedReady = true;
  }
  digitalWrite(LED_PIN, ledState ? LOW : HIGH);

  const unsigned long now = millis();
  if (battery != nullptr && (now - lastBatteryLog) >= BATTERY_LOG_INTERVAL_MS) {
    const float voltage = battery->readVoltage();
    const float percent = battery->readPercentage();
    Serial.printf("Battery: %.2fV (%.0f%%)\n", voltage, percent);
    lastBatteryLog = now;
  }

  delay(BLINK_DELAY_MS);
}
