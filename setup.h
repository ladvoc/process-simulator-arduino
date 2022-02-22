#ifndef SETUP_H
#define SETUP_H
#pragma once

// The number of modules being used.
#define MODULE_COUNT 1

// The model number of each module.
static const char* MODULE_CONFIG[MODULE_COUNT] = {
    "P1-15TD1"//,  // slot 1
    //"P1-16TR",   // slot 2
    //"P1-04DAL-1" // slot 3
};

void performSetup();
static void fatalError(const char* message);

#endif