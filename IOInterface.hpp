/// Copyright © 2022 Jacob Gelman
/// This code is licensed under the MIT License.
/// See the LICENSE file in the project root for license terms.

#include "LEDBus.hpp"
#include "Display.hpp"
#include "config.h"

#ifndef PROCESSIO_H
#define PROCESSIO_H
#pragma once

class Process; // Forward decl.

class IOInterface
{
private:
    static const int INLET_PIN = 0;
    static const int DRAIN_PIN = 1;

    // Storege for current and previous discrete inputs states.
    bool _dinPrev[DIGITAL_IN_COUNT];
    bool _dinCurr[DIGITAL_IN_COUNT];

    // Read all discrete inputs states
    inline void readDiscreteIn();

    // Store current discrete input states for the next iteration.
    inline void storeDiscreteIn();

    // Read control button inputs
    inline void readControlButtons();

    // Helper functions for reading discrete input for a given channel.
    inline bool readDiscreteIn(int channel);
    inline bool isButtonPress(int channel);

    Process *_process;
    LEDBus *_ledBus;
    Display *_disp;

public:
    IOInterface(Process *process);

    // Read current inputs from all sources and feed them into the simulation.
    void readInputs();

    // Write outputs based on the current simulation state.
    void outputCurrentState();
};
#endif