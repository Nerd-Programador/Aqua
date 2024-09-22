#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>

#include "LogSystem.h"

class TempSensor {
public:
    TempSensor(uint8_t pin);
    void begin();
    float getTemperature();

private:
    OneWire oneWire;
    DallasTemperature sensors;
    DeviceAddress sensorAddress; // Para armazenar o endereço do sensor
    bool isValidTemperature(float temperature); // Verifica se a temperatura é válida
};

#endif // TEMPSENSOR_H
