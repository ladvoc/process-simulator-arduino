#include <Arduino.h>
#include <P1AM.h>

#include "setup.h"
#include "Process.hpp"

// TODO:
// 1. Add reset function
// 2. Test alt. GPIO module
// 3. Bug fix: serial
// 4. Bug fix: dont start sim. untill LEDs ready
// 5. Add screen

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