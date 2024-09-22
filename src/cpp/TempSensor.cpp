#include "TempSensor.h"

// Declaração externa do sistema de logs
extern LogSystem logSystem;

TempSensor::TempSensor(uint8_t pin) : oneWire(pin), sensors(&oneWire) {}

void TempSensor::begin() {
    sensors.begin();

    if (!sensors.getAddress(sensorAddress, 0)) {
        // Se o sensor não for encontrado, informe ou faça o tratamento necessário
        logSystem.logEvent("Sensor de temperatura não encontrado!");
    }
    sensors.setResolution(sensorAddress, 12); // Define a resolução do sensor, se necessário
}

float TempSensor::getTemperature() {
    sensors.requestTemperatures();
    float temperature = sensors.getTempC(sensorAddress);

    if (temperature == DEVICE_DISCONNECTED_C || !isValidTemperature(temperature)) {
        logSystem.logEvent("Erro ao ler o sensor de temperatura.");
        return NAN; // Retorna "Not a Number" se a leitura falhar ou estiver fora do intervalo esperado
    }
    return temperature;
}

bool TempSensor::isValidTemperature(float temperature) {
    // Verifica se a temperatura está dentro de um intervalo razoável (exemplo: -10 a 50°C)
    return (temperature > 15.0 && temperature < 30.0);
}
