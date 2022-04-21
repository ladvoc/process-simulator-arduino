#include "LEDBus.hpp"
#include "Display.hpp"

#ifndef PROCESSIO_H
#define PROCESSIO_H
#pragma once

class Process; // Forward decl.

class ProcessIO
{
private:
    static const int INLET_PIN = 0;
    static const int DRAIN_PIN = 1;

    Process *_process;
    LEDBus *_ledBus;
    Display *_disp;

public:
    ProcessIO(Process *process);

    // Read current inputs from all sources and feed them into the simulation
    void readInputs();

    // Write outputs based on the current simulation state
    void outputCurrentState();
};
#endif