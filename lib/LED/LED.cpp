#include "LED.h"

LED::LED(uint8_t pin)
: state(false)
{
  strip = new Adafruit_NeoPixel(1, pin, NEO_GRB + NEO_KHZ800);
  strip->begin();
  strip->setBrightness(255);
  this->setState(this->state);
  strip->clear();
  strip->show();
}

void LED::setState(bool newState) {
  state = newState;
  if (state) {
    strip->setPixelColor(0, strip->Color(255, 255, 255));
  } else {
    strip->setPixelColor(0, 0);
  }
  strip->show();
}

bool LED::getState() const { return state; }
