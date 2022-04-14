#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

#include "Display.hpp"

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT    32
#define SCREEN_RESET     -1 // Share Arduino rest pin
#define SCREEN_ADDRESS 0x3C

Display::Display(){
    _disp = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, SCREEN_RESET);

    if (!_disp->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
    }
}

void Display::update(double fillPercentage) {

    // 1. Clear frame buffer
    _disp->clearDisplay();

    // 2. Draw content
    _disp->setTextSize(2);
    _disp->setTextColor(SSD1306_WHITE);
    _disp->setCursor(0, 0);

    if (fillPercentage <= 0) {
       _disp->print(F("Tank empty "));
    } else if (fillPercentage >= 1) {
       _disp->print(F("Tank full "));
    } else {
       _disp->print(F("Fill "));
      _disp->print((int)(fillPercentage * 100));
      _disp->print(F("%"));

      _disp->drawFastHLine(0, SCREEN_HEIGHT - 4, SCREEN_WIDTH, SSD1306_WHITE);
      _disp->fillRect(0, SCREEN_HEIGHT - 4, SCREEN_WIDTH * fillPercentage, 4, SSD1306_WHITE);
    }

    // 3. Write the frame buffer to the display
    _disp->display();
}