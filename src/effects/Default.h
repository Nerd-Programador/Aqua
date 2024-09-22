#ifndef DEFAULT_H
#define DEFAULT_H

#include <Adafruit_NeoPixel.h>

// Função para desligar todos os LEDs (modo OFF)
inline void turnOff(Adafruit_NeoPixel &strip) {
    strip.clear();  // Limpa todos os LEDs, ou seja, apaga todos
    strip.show();   // Atualiza o strip para aplicar as mudanças
}

// Função para ligar todos os LEDs com brilho máximo (modo ON)
inline void turnOn(Adafruit_NeoPixel &strip) {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 255));  // Define a cor branca com intensidade máxima
    }
    strip.show();  // Atualiza o strip para aplicar as mudanças
}

#endif
