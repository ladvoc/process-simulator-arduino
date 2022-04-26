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

void Display::update(bool isRunning, double fillPercentage, unsigned int param)
{

    // 1. Clear frame buffer
    _disp->clearDisplay();

    // 2. Draw content
    _disp->setTextSize(2);
    _disp->setTextColor(SSD1306_WHITE);
    _disp->setCursor(0, 0);

    if (!isRunning)
    {
        // "Ready" text
        _disp->setCursor(50, HEIGHT * 0.25);
        _disp->print(F("Ready"));
        
        // Param number
        _disp->fillRoundRect(0, 0, 30, HEIGHT, 4, SSD1306_WHITE);
        _disp->setCursor(8, HEIGHT * 0.2);
        _disp->setTextSize(3);
        _disp->setTextColor(SSD1306_BLACK);
        _disp->print(param);
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