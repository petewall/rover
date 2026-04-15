#pragma once

#define LED_PIN LED_BUILTIN  // Built-in LED on D4, active low

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
