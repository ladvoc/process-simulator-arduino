#include <math.h>
#include <Arduino.h>

#include "Process.hpp"

Process::Process()
{
    // Set defaults for simulation variables.
    reset();

    // Simulation is not running initially.
    _isRunning = false;

    // Default parameter.
    _currentParam = 1;

    _io = new IOInterface(this);
}

void Process::reset()
{
    // Any variable directly used in modeling the simulation
    // should be set to its inital value here.

    // Inlet valve starts closed
    _isInletOpen = false;

    // Drain valve starts closed
    _isDrainOpen = false;

    // Tank starts empty
    _liquidVolume = 0;
}

void Process::change()
{
    // If the simulation is running, stop and reset to expose
    // the start screen.
    if (_isRunning) {
        _isRunning = false;
        reset();
        return;
    }

    // Incremenet by one; clamp by PARAM_COUNT.
    _currentParam = _currentParam == PARAM_COUNT ? 1 : _currentParam + 1;
}

void Process::start()
{
     // If the simulation is already running, do nothing.
    if (_isRunning) return;

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