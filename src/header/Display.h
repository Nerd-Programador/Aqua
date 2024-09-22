#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "OTASystem.h"
#include "Credentials.h"
#include "HeaterControl.h"
#include "Lumen.h"
#include "LogSystem.h"

#define SCREEN_WIDTH 128     // Largura do display OLED em pixels
#define SCREEN_HEIGHT 64     // Altura do display OLED em pixels

class Display {
public:
    Display(int width, int height);
    void begin();
    void showTemperature(float temperature);
    void showWiFiInfo();
    void showOTAProgress(unsigned int progress, unsigned int total);
    void showTemporary(const char* message, unsigned long duration = 3000);
    void showError(const char* errorMessage);
    void showHeaterStatus(bool isOn);
    void showHeaterTime(unsigned long timeMillis);

private:
    int screenWidth;
    int screenHeight;
    Adafruit_SSD1306 display;
    void clearArea(int16_t x, int16_t y, int16_t w, int16_t h);
};

#endif
