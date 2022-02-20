#include "FastLED.h"

#ifndef LEDBUS_H
#define LEDBUS_H
#pragma once

// The number of LEDs in the bus
const int LED_COUNT = 26;

// The pin used written to
const int DATA_PIN = 6;

// Indices of the high and low limit indicators
const int H_LIMIT_INDEX = 24;
const int L_LIMIT_INDEX = 25;

// The index of the first LED in the level indicator
const int LEVEL_START_INDEX = 0;

// The number of LEDs in the level indicator
const int LEVEL_LED_COUNT = 24;

class LEDBus
{
	private:
    // An array of RGB values which correspond to the LEDs in the bus
    CRGB _leds[LED_COUNT];

    // Set the state of the indicator LED at the given index
    void _setIndicator(int index, bool isIlluminated);

	public:
		LEDBus();

    // Set the level indicator according to the given value (range 0-1)
    void setLevelIndicator(double value);

    // Turn on/off the high limit indicator
    void setHLimitIndicator(bool isIlluminated);

    // Turn on/off the low limit indicator
    void setLLimitIndicator(bool isIlluminated);

    // Write the current RGB values to the bus
    void update();

		~LEDBus();
};
#endif