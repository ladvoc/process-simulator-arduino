/// Copyright © 2022 Jacob Gelman
/// This code is licensed under the MIT License.
/// See the LICENSE file in the project root for license terms.

#include "FastLED.h"

#ifndef LEDBUS_H
#define LEDBUS_H
#pragma once

class LEDBus
{
private:
    // The number of LEDs in the bus
    static const int LED_COUNT = 26;

    // The pin used written to
    static const int DATA_PIN = 6;

    // The index of the first LED in the level indicator
    static const int LEVEL_START_INDEX = 0;

    // The number of LEDs in the level indicator
    static const int LEVEL_LED_COUNT = 22;

    // Indices of discrete indicators
    static const int INLET_INDEX = 22;
    static const int DRAIN_INDEX = 23;
    static const int L_LIMIT_INDEX = 24;
    static const int H_LIMIT_INDEX = 25;

    // An array of RGB values which correspond to the LEDs in the bus
    CRGB _leds[LED_COUNT];

    // Set the state of the indicator LED at the given index
    void _setIndicator(int index, bool isIlluminated, CRGB onColor);

public:
    LEDBus();

    // Set the level indicator according to the given value (range 0-1)
    void setLevelIndicator(double value);

    // Discrete indicators on/offf
    void setInletValveIndicator(bool isIlluminated);
    void setDrainValveIndicator(bool isIlluminated);
    void setHLimitIndicator(bool isIlluminated);
    void setLLimitIndicator(bool isIlluminated);

    // Write the current RGB values to the bus
    void update();

    ~LEDBus();
};
#endif