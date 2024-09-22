#include <Arduino.h>
#include "Effect.h"

// Variável global para controle de brilho
uint8_t globalBrightness = 255;

// Função para ajustar o brilho global
void setGlobalBrightness(uint8_t brightness) {
    globalBrightness = brightness;
}

// Função auxiliar para aplicar o brilho global
uint32_t applyBrightness(uint32_t color) {
    uint8_t r = (uint8_t)(color >> 16);
    uint8_t g = (uint8_t)(color >> 8);
    uint8_t b = (uint8_t)color;
    
    r = (r * globalBrightness) / 255;
    g = (g * globalBrightness) / 255;
    b = (b * globalBrightness) / 255;
    
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

void turnOff(Adafruit_NeoPixel &strip) {
    strip.clear();
    strip.show();
}

void turnOn(Adafruit_NeoPixel &strip) {
    strip.clear();
    uint32_t color = applyBrightness(strip.Color(255, 255, 255));
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, color);
    }
    strip.show();
}

uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return applyBrightness(Adafruit_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3));
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return applyBrightness(Adafruit_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3));
    } else {
        WheelPos -= 170;
        return applyBrightness(Adafruit_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0));
    }
}

void rainbowCycle(Adafruit_NeoPixel &strip) {
    static uint16_t j = 0;
    static uint32_t lastUpdate = 0;
    const uint32_t interval = 100; // Ajustado para uma transição mais suave

    if (millis() - lastUpdate > interval) {
        lastUpdate = millis();
        for (uint16_t i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }
        strip.show();
        j = (j + 1) & 255;
    }
}

void binaryRGB(Adafruit_NeoPixel &strip) {
    static uint32_t lastUpdate = 0;
    const uint32_t interval = 1000;
    static float angle = 0.0;

    if (millis() - lastUpdate > interval) {
        lastUpdate = millis();
        angle += 0.1;
        if (angle >= TWO_PI) angle -= TWO_PI;

        uint32_t colorA = applyBrightness(strip.Color(
            (sin(angle) + 1) * 127.5,
            (sin(angle + TWO_PI/3) + 1) * 127.5,
            (sin(angle + 2*TWO_PI/3) + 1) * 127.5
        ));
        uint32_t colorB = applyBrightness(strip.Color(255, 255, 255));

        for (uint16_t i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, (i % 2 == 0) ? colorA : colorB);
        }
        strip.show();
    }
}

void dayNightCycle(Adafruit_NeoPixel &strip) {
    static uint16_t timeOfDay = 0;
    static uint32_t lastUpdate = 0;
    const uint32_t interval = 100;

    if (millis() - lastUpdate > interval) {
        lastUpdate = millis();

        uint8_t r, g, b;
        if (timeOfDay < 85) {
            r = g = map(timeOfDay, 0, 85, 20, 255);
            b = r * 0.7;
        } else if (timeOfDay < 170) {
            r = g = b = map(timeOfDay, 85, 170, 255, 100);
        } else {
            b = map(timeOfDay, 170, 255, 100, 20);
            r = g = b * 0.3;
        }

        uint32_t color = applyBrightness(strip.Color(r, g, b));
        for (uint16_t i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, color);
        }
        strip.show();
        timeOfDay = (timeOfDay + 1) & 255;
    }
}

void plantGrowth(Adafruit_NeoPixel &strip) {
    const uint16_t numLeds = strip.numPixels();
    const uint16_t groupSize = 5;
    const uint16_t numGroups = numLeds / groupSize;
    static uint16_t offset = 0;
    static uint32_t lastUpdate = 0;
    const uint32_t interval = 1000;

    if (millis() - lastUpdate > interval) {
        lastUpdate = millis();

        uint32_t colors[] = {
            applyBrightness(strip.Color(255, 0, 0)),
            applyBrightness(strip.Color(0, 0, 255))
        };

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

void moonlightEffect(Adafruit_NeoPixel &strip) {
    static uint8_t brightness = 50;
    static int8_t direction = 1;
    static uint32_t lastUpdate = 0;
    const uint32_t interval = 100; // Ajustado para uma transição mais suave

    if (millis() - lastUpdate > interval) {
        lastUpdate = millis();

        uint32_t color = applyBrightness(strip.Color(0, 0, brightness));
        for (uint16_t i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, color);
        }
        strip.show();

        brightness += direction;
        if (brightness >= 100 || brightness <= 50) {
            direction = -direction;
        }
    }
}
