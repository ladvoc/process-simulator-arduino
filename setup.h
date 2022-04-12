#ifndef SETUP_H
#define SETUP_H
#pragma once

// The number of modules being used.
#define MODULE_COUNT 2

// The model number of each module.
static const char* MODULE_CONFIG[MODULE_COUNT] = {
    "P1-15TD1", // slot 1 (3.3-24VDC sink output)
    "P1-16ND3"  // slot 2 (12-24VDC input)
};

void performSetup();
static void fatalError(const char* message);

#endif