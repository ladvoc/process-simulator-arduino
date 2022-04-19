#include "LEDBus.hpp"
#include "Display.hpp"

#ifndef PROCESSIO_H
#define PROCESSIO_H
#pragma once

class Process; // Forward decl.

class ProcessIO
{
private:
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