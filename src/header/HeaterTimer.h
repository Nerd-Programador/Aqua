#ifndef HEATERTIMER_H
#define HEATERTIMER_H

#include <Arduino.h>

class HeaterTimer {
public:
    HeaterTimer();
    void start(unsigned long duration);  // Inicia o timer com duração em milissegundos
    void stop();  // Para o timer
    void update();  // Verifica o timer e desliga o aquecedor quando o tempo expira

private:
    bool timerActive;
    unsigned long endTime;
};

#endif
