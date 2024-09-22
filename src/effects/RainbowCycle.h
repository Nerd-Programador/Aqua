#ifndef RAINBOW_CYCLE_H
#define RAINBOW_CYCLE_H

#include <Adafruit_NeoPixel.h>

// Função auxiliar para gerar cores baseadas na posição do espectro (0-255)
uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return Adafruit_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        return Adafruit_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return Adafruit_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Função para executar o efeito Rainbow Cycle
inline void rainbowCycle(Adafruit_NeoPixel& strip, int speed) {
    uint16_t i, j;

    for (j = 0; j < 256; j++) { // 256 ciclos completos de cor
        for (i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }
        strip.show();
        delay(1000 / speed);  // Controla a velocidade do ciclo
    }
}

#endif
