#include <Adafruit_SSD1306.h>

#ifndef DISPLAY_H
#define DISPLAY_H
#pragma once

class Display
{
private:
    static const int WIDTH     = 128;
    static const int HEIGHT    = 32;
    static const int RESET_PIN = -1; // Share Arduino rest pin
    static const int ADDR      = 0x3C;

    Adafruit_SSD1306 *_disp;

public:
    Display();
    void update(bool isRunning, double fillPercentage);
};
#endif