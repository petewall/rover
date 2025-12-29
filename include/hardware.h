#pragma once

#define LED_PIN LED_BUILTIN  // Built-in LED on D4, active low
#define RGB_LED_PIN D2

#define PIN_DIN D7
#define PIN_CLK D5
#define PIN_CS  D8

#ifndef LED_DATA_PIN
#define LED_DATA_PIN PIN_DIN
#endif

#ifndef BATTERY_ADC_PIN
#define BATTERY_ADC_PIN A0
#endif

#ifndef BATTERY_FULL_VOLTAGE
#define BATTERY_FULL_VOLTAGE 4.2f
#endif

#ifndef BATTERY_EMPTY_VOLTAGE
#define BATTERY_EMPTY_VOLTAGE 3.0f
#endif

// Wi-Fi credentials are provided via PlatformIO build flags
// e.g., -D WIFI_SSID=... and -D WIFI_PASSWORD=...
#ifndef WIFI_SSID
#define WIFI_SSID ""
#endif
#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD ""
#endif
