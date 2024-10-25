/// Copyright © 2022 Jacob Gelman
/// This code is licensed under the MIT License.
/// See the LICENSE file in the project root for license terms.

#pragma once

// The number of modules being used.
#define MODULE_COUNT 3

// Slot number each type of module is installed in.
#define SINK_OUT_SLOT   1
#define ANALOG_OUT_SLOT 2
#define DIGITAL_IN_SLOT 3

// The number of channels in the digital input module.
#define DIGITAL_IN_COUNT 16

// Component channel numbers.
#define CHANGE_BTN_CH 6
#define RESET_BTN_CH 7
#define START_BTN_CH 8

// The model number of each module.
// An error is reported if this configuration is not found.
static const char *MODULE_CONFIG[MODULE_COUNT] = {
    "P1-15TD1",   // slot 1 (3.3-24VDC sink output)
    "P1-04DAL-1", // slot 2 (4-20mA analog out)
    "P1-16ND3"    // slot 3 (12-24VDC input)
};

#define SERIAL_BAUDRATE 115200

// Enable output of current simulation state
#define SERIAL_DEBUG
