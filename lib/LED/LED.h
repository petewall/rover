#pragma once

#include <Adafruit_NeoPixel.h>

class LED {
 public:
  explicit LED(uint8_t pin);

  void setState(bool on);
  bool getState() const;

 private:
  bool state;
  Adafruit_NeoPixel* strip;
};
