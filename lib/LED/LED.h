#pragma once

#include <Adafruit_NeoPixel.h>

class LED {
 public:
  explicit LED(uint8_t data_pin);

  void begin();
  void setColor(uint8_t red, uint8_t green, uint8_t blue);

  void off();
  void red();
  void green();

  uint8_t getRed();
  uint8_t getGreen();
  uint8_t getBlue();

 private:
  void update();
  Adafruit_NeoPixel strip;
  uint8_t r;
  uint8_t g;
  uint8_t b;
};
