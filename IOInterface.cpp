#include <Arduino.h>
#include <P1AM.h>

#include "config.h"
#include "IOInterface.hpp"
#include "Process.hpp"

IOInterface::IOInterface(Process *process) : _dinPrev{}
{
    _process = process;
    _ledBus = new LEDBus();
    _disp = new Display();

    // Not currently used
    // pinMode(SWITCH_BUILTIN, INPUT);
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
    _disp->update(_process->isRunning(), _process->fillPercentage(), _process->currentParam());

#ifdef SERIAL_DEBUG
    Serial.flush();
    Serial.println("Simulation state:");
    Serial.print("Parameter number: ");
    Serial.println(_process->currentParam());
    if (_process->isRunning())
    {
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
    }
    else
    {
        Serial.println("Simulation not running");
    }
#endif
}

void IOInterface::readInputs()
{
    // 1. Read state from discrete input module
    readDiscreteIn();

    // 2. Check control button states, act accordingly
    readControlButtons();

    // 3. Store discrete input state for the next iteration
    storeDiscreteIn();
}

inline void IOInterface::readControlButtons()
{
    // Start the simulation when start button pressed
    if (isButtonPress(START_BTN_CH))
        _process->start();

    // Change the simulation param. when the "change" button is pressed
    if (isButtonPress(CHANGE_BTN_CH))
        _process->change();

    // Reset the simulation if the reset button is pressed
    if (isButtonPress(RESET_BTN_CH))
        _process->reset();
}

inline void IOInterface::readDiscreteIn()
{
    // Read all channels
    uint16_t inputs = P1.readDiscrete(DIN_SLOT);

    // Convert to bool array
    for (int i = 0; i < sizeof(_dinCurr); i++)
        _dinCurr[i] = inputs & (1 << i);
}

inline void IOInterface::storeDiscreteIn()
{
    memcpy(_dinPrev, _dinCurr, sizeof(_dinCurr));
}

inline bool IOInterface::readDiscreteIn(int channel)
{
    // Convert to array index, read value
    return _dinCurr[channel - 1];
}

inline bool IOInterface::isButtonPress(int channel)
{
    // Convert to array index
    channel -= 1;

    // True when channel from low to high occured
    return _dinCurr[channel] == HIGH &&
           _dinPrev[channel] == LOW;
}
