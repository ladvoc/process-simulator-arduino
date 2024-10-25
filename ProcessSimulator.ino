/// Copyright © 2022 Jacob Gelman
/// This code is licensed under the MIT License.
/// See the LICENSE file in the project root for license terms.

#include <Arduino.h>
#include <P1AM.h>

#include "config.h"
#include "Process.hpp"

// TODO:
// 1. Add reset function
// 2. Test alt. GPIO module
// 3. Bug fix: serial
// 4. Bug fix: dont start sim. untill LEDs ready
// 5. Add screen [x]

// Reference to the simulation
Process *process;

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);

    // Wait for modules to come online.
    while (!P1.init()) {}

    // Print current module configuration and firmware version.
    P1.printModules();
    P1.getFwVersion();

    // Ensure modules are plugged in as expected.
    uint8_t errorFlags = P1.rollCall(MODULE_CONFIG, MODULE_COUNT);
    if (errorFlags != 0)
    {
        // Turn on the yellow LED.
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, HIGH);

        // Print the given message every ten seconds until power is cycled.
        while (true)
        {
            Serial.println("Module error");
            delay(10000);
        }
    }

    process = new Process();
}

void loop()
{
    process->simulateStep();
}