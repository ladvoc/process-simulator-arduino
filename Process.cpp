#include <math.h>
#include <Arduino.h>

#include "Process.hpp"

Process::Process()
{
    reset();
    _io = new IOInterface(this);
}

void Process::reset()
{
    _currentParam = 1;
    _isRunning = false;   // Wait for user to start the sim.
    _isInletOpen = false; // Inlet valve starts closed
    _isDrainOpen = false; // Drain valve starts closed
    _liquidVolume = 0;    // Tank starts empty
}

void Process::change()
{
    // If the simulation is running, do nothing.
    if (_isRunning) return;

    // Incremenet by one; clamp by PARAM_COUNT.
    _currentParam = _currentParam == PARAM_COUNT ? 1 : _currentParam + 1;
}

void Process::start()
{
    _isRunning = true;
    _lastUpdateTime = millis();
}

void Process::simulateStep()
{
    // 1. Read inputs
    _io->readInputs();

    // 2. Update simulation state accodingly
    _updateState();

    // 2. Display
    _io->outputCurrentState();
}

void Process::_updateState()
{
    // Do not run simulation until start() called
    if (!_isRunning) return;

    // How much time (in seconds) has passed since the last update
    double stepTime = (millis() - _lastUpdateTime) / 1000;

    // Fill & drain according to valve state and time passed
    if (_isInletOpen)
        _liquidVolume += INLET_FLOWRATE * stepTime;
    if (_isDrainOpen)
        _liquidVolume -= DRAIN_FLOWRATE * stepTime;

    // Handle overflow and underflow conditions
    if (_liquidVolume > TANK_CAPACITY)
        _liquidVolume = TANK_CAPACITY;
    if (_liquidVolume < 0)
        _liquidVolume = 0;

    // Update time
    _lastUpdateTime = millis();
}

bool Process::isAtHLimit() const
{
    // Is at high limit when the current liquid volume is
    // greater than or equal to the volume at the high limit switch
    return _liquidVolume >= HLIMIT_VOL;
}

bool Process::isAtLLimit() const
{
    // Is at low limit when the current liquid volume is
    // greater than or equal to the volume at the low limit switch
    return _liquidVolume >= LLIMIT_VOL;
}

double Process::fillPercentage() const
{
    return _liquidVolume / TANK_CAPACITY;
}

Process::~Process()
{
    delete _io;
}