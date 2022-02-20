#include <Arduino.h>
#include <P1AM.h>

#include "setup.h"
#include "Process.hpp"

// Time between computing simulation steps
const int STEP_DELAY = 500;

// Reference to the simulation
Process* process;

void setup() {
  performSetup(); 
  process = new Process();
}

void loop() {
  process->simulateStep();
  delay(STEP_DELAY);
}