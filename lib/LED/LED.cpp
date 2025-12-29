#include "LED.h"

LED::LED(uint8_t data_pin)
    : strip(1, data_pin, NEO_GRB + NEO_KHZ800), r(0), g(0), b(0) {}

void LED::begin() {
  strip.begin();
}

void LED::setColor(uint8_t red, uint8_t green, uint8_t blue) {
  r = red;
  g = green;
  b = blue;
  update();
}

void LED::off() { setColor(0, 0, 0); }
void LED::red() { setColor(255, 0, 0); }
void LED::green() { setColor(0, 255, 0); }

uint8_t LED::getRed() { return r; }
uint8_t LED::getGreen() { return g; }
uint8_t LED::getBlue() { return b; }

void LED::update() {
  strip.setPixelColor(0, strip.Color(r, g, b));
  strip.show();
}
