#include <Adafruit_SSD1306.h>

#ifndef DISPLAY_H
#define DISPLAY_H
#pragma once

class Display
{
private:
    Adafruit_SSD1306 *_disp;

public:
    Display();
    void update(double fillPercentage);
};
#endif