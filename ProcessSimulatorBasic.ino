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
    #ifdef SERIAL_DEBUG
    Serial.begin(BAUDRATE);
    #endif

    // Wait for modules to come online.
    while (!P1.init()) {}

    // Ensure modules are plugged in as expected.
    uint8_t errorFlags = P1.rollCall(MODULE_CONFIG, MODULE_COUNT);
    if (errorFlags != 0) {

        // Turn on the yellow LED.
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, HIGH);

        // Print the given message every ten seconds until power is cycled.
        while (true) {
            #ifdef SERIAL_DEBUG
            Serial.println("Modules not plugged in correctly.");
            #endif
            delay(10000);
        }
    }

    process = new Process();
}

void loop()
{
    process->simulateStep();
}