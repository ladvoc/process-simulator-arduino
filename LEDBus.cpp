#include "FastLED.h"

#include "LEDBus.hpp"

LEDBus::LEDBus() {
  // Initalize communication with LEDs
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(_leds, LED_COUNT);

  // Limit the output brightness to 20% (scale 0-255)
  FastLED.setBrightness(50);

  // Turn all LEDs off
  fill_solid(_leds, LED_COUNT, CRGB::Black);
}

void LEDBus::setLevelIndicator(double value) {

  // Fill the appropriate number of LEDs based on the value
  int numOn  = LEVEL_LED_COUNT * value;
  int numOff = LEVEL_LED_COUNT - numOn;

  // Pointer to the first LED
  CRGB* first = _leds + LEVEL_START_INDEX;

  // Fill as required
  fill_solid(first, numOn, CRGB::Blue);
  fill_solid(first + numOn, numOff, CRGB::Black);
}

void LEDBus::_setIndicator(int index, bool isIlluminated, CRGB onColor) {
  _leds[index] = isIlluminated ? onColor : CRGB::Black;
}

void LEDBus::setInletValveIndicator(bool isIlluminated) {
  _setIndicator(INLET_INDEX, isIlluminated, CRGB::Turquoise);
}

void LEDBus::setDrainValveIndicator(bool isIlluminated) {
  _setIndicator(DRAIN_INDEX, isIlluminated, CRGB::Turquoise);
}

void LEDBus::setHLimitIndicator(bool isIlluminated) {
  _setIndicator(H_LIMIT_INDEX, isIlluminated, CRGB::Purple);
}

void LEDBus::setLLimitIndicator(bool isIlluminated) {
  _setIndicator(L_LIMIT_INDEX, isIlluminated, CRGB::Purple);
}

void LEDBus::update() {
  FastLED.show();
}

LEDBus::~LEDBus() {}