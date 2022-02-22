#include <Arduino.h>
#include <P1AM.h>

#include "ProcessIO.hpp"
#include "Process.hpp"  

#define INLET_PIN 0
#define DRAIN_PIN 1

ProcessIO::ProcessIO(Process* process) {
    _process = process;
    _ledBus = new LEDBus();

    // Configure inputs
    // pinMode(INLET_PIN, INPUT_PULLUP);
    // pinMode(DRAIN_PIN, INPUT_PULLUP);
    pinMode(SWITCH_BUILTIN, INPUT);
}

void ProcessIO::outputCurrentState()
{
  // Write the current state of the high and low limit switches
  // to the 3.3-24VDC sink output module installed in slot 1
  P1.writeDiscrete(_process->isAtHLimit(), 1, 1);
  P1.writeDiscrete(_process->isAtLLimit(), 1, 2);

  // Update LED bus
  _ledBus->setLevelIndicator(_process->fillPercentage());
  _ledBus->setDrainValveIndicator(_process->isDrainOpen());
  _ledBus->setInletValveIndicator(_process->isInletOpen());
  _ledBus->setHLimitIndicator(_process->isAtHLimit());
  _ledBus->setLLimitIndicator(_process->isAtLLimit());
  _ledBus->update();

  #ifdef WRITE_TO_SERIAL
  Serial.flush();
  Serial.println("Simulation state:");
  Serial.print("Tank fill percentage: ");
  Serial.println(_process->fillPercentage());
  Serial.print("Inlet valve: ");
  Serial.println(_process->isInletOpen() ? "OPEN" : "CLOSED");
  Serial.print("Drain valve: ");
  Serial.println(_process->isDrainOpen() ? "OPEN" : "CLOSED");
  Serial.print("At high limit: ");
  Serial.println(_process->isAtHLimit() ? "YES" : "NO");
  Serial.print("At low limit: ");
  Serial.println(_process->isAtLLimit() ? "YES" : "NO");
  Serial.println();
  #endif
}

void ProcessIO::readInputs() {
  // When the built-in switch is on, fill the tank; when it is off, drain the tank
  _process->setInletState(digitalRead(SWITCH_BUILTIN) == HIGH);
  _process->setDrainState(digitalRead(SWITCH_BUILTIN) == LOW);
}
