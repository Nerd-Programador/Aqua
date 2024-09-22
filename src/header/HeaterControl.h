#ifndef HEATERCONTROL_H
#define HEATERCONTROL_H

#include <Arduino.h>  // Adiciona a biblioteca Arduino.h para o tipo uint8_t e funções básicas

#include "Display.h"
#include "LogSystem.h"
#include "TempSensor.h"

const unsigned long MAX_HEATER_ON_TIME = 3600000; // 1 hora em milissegundos

class HeaterControl {
public:
    HeaterControl(uint8_t pin);  // Construtor que recebe o pino do relé
    void begin();                // Inicializa o pino do relé
    void update(float temperature, bool sensorError); // Atualiza o estado do aquecedor com base na temperatura e verifica erros
    void turnHeaterOn();         // Liga o aquecedor
    void turnHeaterOff();        // Desliga o aquecedor
    bool isHeaterOn();           // Retorna o estado atual do aquecedor

    // Adiciona o método que retorna o tempo de início do aquecedor
    unsigned long getHeaterOnStartTime() {
        return heaterOnStartTime;
    }

private:
    uint8_t heaterPin;   // Pino conectado ao relé do aquecedor
    bool heaterState;    // Estado atual do aquecedor (ligado/desligado)
    bool overheat;       // Indica se o aquecedor está em estado de sobrecarga
    unsigned long timeInRange;  // Tempo acumulado em que a temperatura esteve na faixa desejada
    unsigned long lastCheck;    // Tempo da última verificação
    unsigned long heaterOnStartTime = 0; // Declaração correta da variável dentro da classe
};

#endif // HEATERCONTROL_H
