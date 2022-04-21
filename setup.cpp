#include <Arduino.h>
#include <P1AM.h>
#include "setup.h"

void performSetup()
{

    Serial.begin(115200);

    // Wait for modules to come online.
    while (!P1.init())
    {
    }

    // Print current module configuration and firmware version.
    P1.printModules();
    P1.getFwVersion();

    // Ensure modules are plugged in as expected.
    uint8_t errorFlags = P1.rollCall(MODULE_CONFIG, MODULE_COUNT);
    if (errorFlags != 0)
    {
        fatalError("Modules not plugged in correctly.");
    }
}

static void fatalError(const char *message)
{

    // Turn on the yellow LED.
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    // Print the given message every ten seconds until power is cycled.
    while (true)
    {
        Serial.println(message);
        delay(10000);
    }
}