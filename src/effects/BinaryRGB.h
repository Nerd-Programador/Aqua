#ifndef BINARY_RGB_H
#define BINARY_RGB_H

#include <Adafruit_NeoPixel.h>

// Função para executar o efeito Binary RGB
inline void binaryRGB(Adafruit_NeoPixel& strip, int speed) {
    int numLeds = strip.numPixels();

    for (int i = 0; i < numLeds; i++) {
        if (i % 2 == 0) {
            // LEDs pares: ciclo RGB
            uint32_t color = strip.Color(
                (sin(speed * 0.1 + 0) + 1) * 127.5,   // Vermelho
                (sin(speed * 0.1 + 2) + 1) * 127.5,   // Verde
                (sin(speed * 0.1 + 4) + 1) * 127.5    // Azul
            );
            strip.setPixelColor(i, color);
        } else {
            // LEDs ímpares: branco
            strip.setPixelColor(i, strip.Color(255, 255, 255));
        }
    }
    strip.show();
    delay(1000 / speed);  // Controla a velocidade do ciclo
}

#endif
