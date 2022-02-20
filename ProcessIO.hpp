#include "LEDBus.hpp"

#ifndef PROCESSIO_H
#define PROCESSIO_H
#pragma once

// If enabled, current simulation state is written over serial
#define WRITE_TO_SERIAL

class Process; // Forward decl.

class ProcessIO
{
	private:
		Process* _process;
    LEDBus* _ledBus;

	public:
		ProcessIO(Process* process);
    
    // Read current inputs from all sources and feed them into the simulation
		void readInputs();

    // Write outputs based on the current simulation state
		void outputCurrentState();
};
#endif