#include "ProcessIO.hpp"

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
    // Reference to the IO interface
    ProcessIO *_io;

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

    // Begin running the simulation.
    void start();

    // Whether or not the simulation has been started.
    bool isRunning() { return _isRunning; }

    // Reset the simulation to its inital state
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