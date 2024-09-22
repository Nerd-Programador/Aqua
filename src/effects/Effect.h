#ifndef EFFECT_H
#define EFFECT_H

#include <Adafruit_NeoPixel.h>

void turnOff(Adafruit_NeoPixel& strip);
void turnOn(Adafruit_NeoPixel& strip);
void rainbowCycle(Adafruit_NeoPixel &strip);
void binaryRGB(Adafruit_NeoPixel &strip);
void dayNightCycle(Adafruit_NeoPixel &strip);
void plantGrowth(Adafruit_NeoPixel &strip);
void moonlightEffect(Adafruit_NeoPixel &strip);

#endif
