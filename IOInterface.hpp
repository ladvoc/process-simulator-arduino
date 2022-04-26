#include "LEDBus.hpp"
#include "Display.hpp"

#ifndef PROCESSIO_H
#define PROCESSIO_H
#pragma once

class Process; // Forward decl.

class IOInterface
{
private:
    static const int INLET_PIN = 0;
    static const int DRAIN_PIN = 1;

    // The slot in which the discrete input module is installed
    static const int DIN_SLOT  = 2;

    // The number of channels provided by the discrete input module
    static const int DIN_CH_COUNT = 16;

    // Storege for current and previous discrete inputs states
    bool _dinPrev[DIN_CH_COUNT];
    bool _dinCurr[DIN_CH_COUNT];

    // Read all discrete inputs states
    void readDiscreteIn();

    // Helper functions for reading discrete input
    // from a given channel.
    inline bool readDiscreteIn(int channel);
    inline bool isButtonPress(int channel);

    Process *_process;
    LEDBus *_ledBus;
    Display *_disp;

public:
    IOInterface(Process *process);

    // Read current inputs from all sources and feed them into the simulation
    void readInputs();

    // Write outputs based on the current simulation state
    void outputCurrentState();
};
#endif