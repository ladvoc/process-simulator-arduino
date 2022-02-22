# Process Simulator Basic

## Hardware Overview

<img align="center" width="200" src="/images/1.png">
  
   The simulator defined in this repository models a process consisting of the following physical components:

  | Component | Description |
  | --------- | ----------- |
  | Tank | A hollow cylinder with finite dimensions is used to store a liquid. |
  | Inlet valve | An electronically controlled valve that can be opened or closed to control the inflow of a pressurized liquid. |
  | Drain valve | A secondary, electronically controlled valve that can be opened to allow gravity to drain the liquid in the tank. |
  | High limit | A sensor mounted near the top of the tank used to detect when the liquid is at or above that height. |
  | Low limit | A sensor mounted near the bottom of the tank used to detect when the liquid is at or above that height. |
  
### Potential application
A potential use-case for this tank configuration is in a fire suppression system. In this application, the tank is filled with water to the upper limit through the inlet; if an unexpected drop in water occurs, more is added automatically. In the event of a fire, the drain is opened to rapidly release the tank's contents to suppress the fire. The fire itself could be detected with the addition of a smoke detection sensor or a push-button pressed by an operator.

## Control Overview
A PLC controls the filling and draining of the tank based on the inputs from the limit switches. The logic used depends on the application.

<p align="center">
  <img width="600" src="/images/2.png">
</p>

### Abstraction of the physical process
The "Physical Process" is drawn in the shape of a cloud to indicate that the process may be run as a simulation. In this scenario, the PLC's inputs and outputs are directed towards a simulator in place of actual hardware (i.e. solenoid valves and photoelectric sensors). However, from PLC's perspective, there need not be any alteration to the inputs, outputs, or logic if the process is being simulated.

## Implementation of the Simulator

### Hardware
The simulator's hardware consists of a [P1AM-100](https://www.automationdirect.com/open-source/home) Arduino-based CPU, I/O modules, and a bus of WS2812B addressable LEDs to indicate the current state of the tank, valves, and limit sensors. Additionally, a push-button allows the simulation to be reset.

<p align="center">
  <img width="800" src="/images/3.png">
</p>

#### LED bus
Currently, the LED bus consists of 26 LEDs. The first 21 are used to indicate the current fill percentage of the tank by illuminating the appropriate number of LEDs in the series. For example, if the tank is 55% full, then 12 out of 21 will be illuminated (⌈0.55 * 21⌉ = 12). The remaining LEDs are used as discrete state indicators for the valves and limit sensors.

![LED layout](/images/4.png)

#### Display panel
The simulator along with the PLC interacting with it is integrated into a Pelican case. The upper panel of the case will illustrate the physical hardware components being simulated, and the LEDs will display the current state of each component.
### Software
This repository contains the Arduino sketch powering the simulator. The following flow diagram provides a high-level overview of how the program operates:

<p align="center">
  <img width="600" src="/images/5.png">
</p>

#### Modeling the physical process
The simulation is modeled to reflect the physical process as closely as possible; constants are used to define physical characteristics such as the dimensions of the cylindrical tank, how long it should tank to fill and empty the tank, and the vertical height at which the limit sensors are mounted. From these constants, additional values are calculated such as the volume inside the tank and the flow rates required to achieve the desired fill and drain times.

The simulation could be made more realistic by accounting for the following variables which may be present in the equivalent physical process.
- Flowrate variation: the rate at which liquid enters or exits the tank may not be constant.
- Valve latency: when the PLC orders a valve to open or close, it takes time for the valve to respond mechanically; during this time, liquid may flow at a reduced rate or not at all.

#### Class structure
The program is structured into two key components to provide a level of abstraction between the simulation and how it is controlled and presented:

##### `Process`:
Where the actual simulation is performed; it holds an internal representation of the simulation state (i.e. the volume of liquid in the tank), and provides an interface to set the simulation inputs, calculate the new state, and read the updated state.

##### `ProcessIO`
Responsible for interfacing the simulation with the outside world; it reads the inputs from the PLC (i.e. valve state), passes them to `Process`, and receives back the new state. That new state is then passed to the outside world; the LEDs and the discrete outputs read by the PLC are updated.

#### Dependencies

- [P1AM](https://github.com/facts-engineering/P1AM): provides a high-level interface to features specific to the P1AM-100 CPU and compatible IO modules.
- [FastLED](https://fastled.io): a popular Arduino library for controlling addressable RGB LEDs. A series of LEDs is modeled in-memory as an array in which each element represents the RGB value of an individual LED. These RGB values are written over the LED's data bus by calling a write method.

## Build Procedure
In the [Arduino IDE](https://www.arduino.cc/en/software), select "Manage Libraries," search for each dependency listed above, and press install if required. Next, under settings, add the following URL in the "Additional Board Manager URLs" field:
```
https://raw.githubusercontent.com/facts-engineering/facts-engineering.github.io/master/package_productivity-P1AM-boardmanagermodule_index.json
```
With this URL added, select "Boards Manager" and install the board definition for "P1AM-100." With the CPU attached via USB and the apporiate serial port selected, the sketch can now be built and uploaded.

## Unresolved Issues
- The circuitry within the P1AM-GPIO module distorts the signal sent over the LED data bus—this results in the LEDs behaving erratically. The current workaround is remove the module and interface with the GPIO directly.

## Links
- [P1AM Documentation](https://facts-engineering.github.io): includes FAQs, a module configuration tool, and API reference.