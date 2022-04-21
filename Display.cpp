#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

#include "Display.hpp"

Display::Display()
{
    _disp = new Adafruit_SSD1306(WIDTH, HEIGHT, &Wire, RESET_PIN);

    if (!_disp->begin(SSD1306_SWITCHCAPVCC, ADDR))
    {
        Serial.println(F("SSD1306 allocation failed"));
    }
}

void Display::update(bool isRunning, double fillPercentage)
{

    // 1. Clear frame buffer
    _disp->clearDisplay();

    // 2. Draw content
    _disp->setTextSize(2);
    _disp->setTextColor(SSD1306_WHITE);
    _disp->setCursor(0, 0);

    if (!isRunning)
    {
        // Simulation is not running when fill percentage is < 0
        _disp->setTextSize(2);
        _disp->setCursor(0, 0);
        _disp->println(F("Press\nStart"));
        _disp->setCursor(WIDTH / 2, HEIGHT / 2);
        _disp->println(F(">>"));
    } else {
        // Display tank fill percentage
        _disp->print(F("Fill: "));
        _disp->print((int)(fillPercentage * 100));
        _disp->print(F("%"));

        // Progress bar
        _disp->drawRoundRect(0, HEIGHT - 8, WIDTH, 8, 4, SSD1306_WHITE);
        _disp->fillRoundRect(0, HEIGHT - 8, WIDTH * fillPercentage, 8, 4, SSD1306_WHITE);
    }

    // 3. Write buffer to display
    _disp->display();
}