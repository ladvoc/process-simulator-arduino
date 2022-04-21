#include <Arduino.h>
#include <P1AM.h>

#include "IOInterface.hpp"
#include "Process.hpp"

IOInterface::IOInterface(Process *process)
{
    _process = process;
    _ledBus = new LEDBus();
    _disp = new Display();

    // Configure inputs
    // pinMode(INLET_PIN, INPUT_PULLUP);
    // pinMode(DRAIN_PIN, INPUT_PULLUP);
    pinMode(SWITCH_BUILTIN, INPUT);
}

void IOInterface::outputCurrentState()
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

    // Update the display
    _disp->update(_process->isRunning(), _process->fillPercentage());

#ifdef SERIAL_DEBUG
    Serial.flush();
    Serial.println("Simulation state:");
    if (_process->isRunning()) {
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
    } else {
        Serial.println("Simulation not running");
    }
#endif
}

void IOInterface::readInputs()
{

    // Reset the simulation if the reset button is pressed
    // TODO: hold to reset
    if (P1.readDiscrete(2, 7) == HIGH)
    {
        _process->reset();
    }

    // Start the simulation when start button pressed
    if (P1.readDiscrete(2, 8) == HIGH)
    {
        _process->start();
    }

    // TODO: read from discrete inputs
    // When the built-in switch is on, fill the tank; when it is off, drain the tank
    _process->setInletState(digitalRead(SWITCH_BUILTIN) == HIGH);
    _process->setDrainState(digitalRead(SWITCH_BUILTIN) == LOW);
}
