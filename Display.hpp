#include <Adafruit_SSD1306.h>

#pragma once

class Display
{
private:
    Adafruit_SSD1306 *_disp;

public:
    Display();
    void update(bool isRunning, double fillPercentage);
};