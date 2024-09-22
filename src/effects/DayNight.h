#ifndef DAY_NIGHT_CYCLE_H
#define DAY_NIGHT_CYCLE_H

#include <Adafruit_NeoPixel.h>

// Função para executar o ciclo de dia e noite
inline void dayNightCycle(Adafruit_NeoPixel& strip, int speed) {
    static int timeOfDay = 0;  // Representa o "tempo" no ciclo, varia de 0 a 255

    for (int i = 0; i < strip.numPixels(); i++) {
        // Amanhecer (amarelo claro para branco)
        if (timeOfDay < 85) {
            uint8_t brightness = map(timeOfDay, 0, 85, 20, 255);
            strip.setPixelColor(i, strip.Color(brightness, brightness, (brightness * 0.7)));  // Luz amarelada
        }
        // Meio-dia (branco brilhante)
        else if (timeOfDay < 170) {
            uint8_t brightness = map(timeOfDay, 85, 170, 255, 100);
            strip.setPixelColor(i, strip.Color(brightness, brightness, brightness));  // Luz branca
        }
        // Anoitecer (branco para azul claro)
        else {
            uint8_t brightness = map(timeOfDay, 170, 255, 100, 20);
            strip.setPixelColor(i, strip.Color((brightness * 0.3), (brightness * 0.3), brightness));  // Luz azulada
        }
    }
    
    strip.show();
    timeOfDay = (timeOfDay + speed) % 256;  // Avança no tempo do ciclo e volta para 0 ao alcançar 256
    delay(100);  // Controla a suavidade da transição
}

#endif
