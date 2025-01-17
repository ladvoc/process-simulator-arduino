/// Copyright © 2022 Jacob Gelman
/// This code is licensed under the MIT License.
/// See the LICENSE file in the project root for license terms.

#include "IOInterface.hpp"

#ifndef PROCESS_H
#define PROCESS_H
#pragma once

// Dimensions of the cylindrical tank [meters]
const double TANK_RADIUS = 0.25;
const double TANK_HEIGHT = 3;

// Mounting locations of limit switches [meters]
const double HLIMIT_HEIGHT = 2.8;
const double LLIMIT_HEIGHT = 0.5;

// Volume inside the tank [cubic meters]
const double TANK_CAPACITY = M_PI * pow(TANK_RADIUS, 2) * TANK_HEIGHT;

// Liquid volume at limit switch locations [cubic meters]
const double HLIMIT_VOL = M_PI * pow(TANK_RADIUS, 2) * HLIMIT_HEIGHT;
const double LLIMIT_VOL = M_PI * pow(TANK_RADIUS, 2) * LLIMIT_HEIGHT;

// How long it should take to fill & empty the tank [seconds]
const double FILL_TIME = 20;  // 50
const double EMPTY_TIME = 15; // 40

// The required flowrates to acheive the fill & empty times defined above
const double INLET_FLOWRATE = TANK_CAPACITY / FILL_TIME;
const double DRAIN_FLOWRATE = TANK_CAPACITY / EMPTY_TIME;

class Process
{
private:
    // The number of parameter numbers avalible
    static const unsigned int PARAM_COUNT = 9;

    // Current parameter number
    unsigned int _currentParam;

    // Reference to the IO interface
    IOInterface *_io;

    // Whether or not the simulation has been started
    bool _isRunning;

    // Whether or not liquid is currently flowing into the tank
    bool _isInletOpen;

    // Whether the tank is currently draining
    bool _isDrainOpen;

    // Current volume of liquid in the tank
    double _liquidVolume;

    // When the simulation was last updated
    double _lastUpdateTime;

    // Update the simulation state based on current inputs
    void _updateState();

public:
    Process();

    // Change the current parameter number.
    void change();

    // Begin running the simulation.
    void start();

    // Stop running the simulation.
    void stop();

    // Check the current parameter number
    unsigned int currentParam() const { return _currentParam; }

    // Whether or not the simulation has been started.
    bool isRunning() const { return _isRunning; }

    // Reset the simulation to its inital state. If the
    // simulation was running, it will continue to run.
    void reset();

    // Perform a single simulation step and update outputs
    void simulateStep();

    // Get/set the state of the liquid valve
    void setInletState(bool isOpen) { _isInletOpen = isOpen; }
    bool isInletOpen() const { return _isInletOpen; }

    // Get/set the state of the drain valve
    void setDrainState(bool isOpen) { _isDrainOpen = isOpen; }
    bool isDrainOpen() const { return _isDrainOpen; }

    // Whether or not the liquid is at or above the high limit switch
    bool isAtHLimit() const;

    // Whether or not the liquid is at or above the low limit switch
    bool isAtLLimit() const;

    // How much liquid the tank is currently holding:
    // range 0-1; 0 = empty, 1 = full
    double fillPercentage() const;

    ~Process();
};
#endif