#ifndef PLANT_GROWTH_H
#define PLANT_GROWTH_H

#include <Adafruit_NeoPixel.h>  // Certifique-se de incluir a biblioteca necessária

inline void plantGrowth(Adafruit_NeoPixel &strip, int speed) {
    const uint16_t numLeds = strip.numPixels();
    const uint16_t groupSize = 5;
    const uint16_t numGroups = numLeds / groupSize;
    static uint16_t offset = 0;
    static uint32_t lastUpdate = 0;

    // Velocidade do deslocamento
    uint32_t interval = 1000 / speed;

    if (millis() - lastUpdate > interval) {
        lastUpdate = millis();

        uint32_t colors[] = {strip.Color(255, 0, 0), strip.Color(0, 0, 255)};

        for (uint16_t i = 0; i < numGroups; i++) {
            uint32_t color = colors[(i + offset) % 2];
            for (uint16_t j = 0; j < groupSize; j++) {
                uint16_t ledIndex = (i * groupSize + j) % numLeds;
                strip.setPixelColor(ledIndex, color);
            }
        }

        offset = (offset + 1) % numGroups;

        strip.show();
    }
}

#endif
