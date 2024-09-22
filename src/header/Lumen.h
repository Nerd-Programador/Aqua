#ifndef LUMEN_H
#define LUMEN_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>
#include "Display.h"
#include "LogSystem.h"

#include "Effect.h"
/* #include "Default.h"
#include "PlantGrowth.h"
#include "BinaryRGB.h"
#include "RainbowCycle.h"
#include "DayNight.h"
// #include "MoonLight.h" */

// Enum para os modos de iluminação
enum LightingMode {
    OFF,
    ON,
    PLANT_GROWTH,
    BINARY_RGB,
    RAINBOW_CYCLE,
    DAY_NIGHT_CYCLE,
    MOONLIGHT_EFFECT,
    NUM_MODES
};

class Lumen {
public:
    Lumen(int numLeds, int ledPin, int btnRightPin, int btnLeftPin);

    void begin();
    void update();
    void applyMode();
    void showFeedback();

    // Novas funções para lidar com os modos e botões
    void nextMode();
    void previousMode();
    void updateCurrentSpeed();
    void handleButtons();

    Adafruit_NeoPixel& getStrip();  // Adiciona este método para acessar o strip de LEDs

private:
    Adafruit_NeoPixel strip;
    int btnRightPin;
    int btnLeftPin;
    int currentMode;

    // Debouncers para os botões
    Bounce btnRight;
    Bounce btnLeft;

};

#endif
