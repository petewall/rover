#pragma once

#include <Arduino.h>

class Battery {
 public:
  explicit Battery(uint8_t pin);

  float readVoltage();
  float readPercentage();

 private:
  uint8_t pin;
  float sampleVoltage() const;

  static constexpr float kAdcResolution = 1023.0f;
  static constexpr float kAdcReference = 1.0f;       // ESP8266 ADC reference
  // Combined resistor ratio:
  //   VBAT -> 120k -> (A0) -> 220k -> (ADC) -> 100k -> GND
  //   ADC voltage = VBAT * (320k / (120k + 320k)) * (100k / 320k) ≈ VBAT * 0.227
  static constexpr float kDividerRatio = 0.227f;
};
