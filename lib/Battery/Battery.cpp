#include "Battery.h"

#include "hardware.h"

Battery::Battery(uint8_t pin)
: pin(pin)
{
  pinMode(pin, INPUT);
}

float Battery::sampleVoltage() const {
  const float raw = static_cast<float>(analogRead(pin));
  const float adc_voltage = (raw / kAdcResolution) * kAdcReference;
  return adc_voltage / kDividerRatio;
}

float Battery::readVoltage() { return sampleVoltage(); }

float Battery::readPercentage() {
  const float voltage = readVoltage();
  const float range = BATTERY_FULL_VOLTAGE - BATTERY_EMPTY_VOLTAGE;
  if (range <= 0.0f) {
    return 0.0f;
  }
  float percent = (voltage - BATTERY_EMPTY_VOLTAGE) / range;
  percent = constrain(percent, 0.0f, 1.0f);
  return percent * 100.0f;
}
