#include "HeaterControl.h"

// Declaração externa do objeto Display
extern Display display;
// Declaração externa do sistema de logs
extern LogSystem logSystem;

// Construtor que inicializa o pino do relé, o estado inicial do aquecedor, e o estado de sobrecarga
HeaterControl::HeaterControl(uint8_t pin)
    : heaterPin(pin), heaterState(false), overheat(false), timeInRange(0), lastCheck(0) {}

void HeaterControl::begin() {
    pinMode(heaterPin, OUTPUT);
    turnHeaterOff();  // Garante que o aquecedor comece desligado
}

void HeaterControl::turnHeaterOn() {
    if (!heaterState && !overheat) {  // Evita ligar se estiver em estado de sobrecarga
        digitalWrite(heaterPin, LOW); // Liga o relé com lógica inversa para ligar o aquecedor
        heaterState = true;
        //heaterOnStartTime = millis();
        display.showHeaterStatus(true);

        // Registra no log quando o aquecedor é ligado
        logSystem.logEvent("Aquecedor foi ligado.");
    }
}

void HeaterControl::turnHeaterOff() {
    if (heaterState) {
        digitalWrite(heaterPin, HIGH);  // Desliga o relé com lógica inversa para desligar o aquecedor
        heaterState = false;
        display.showHeaterStatus(false);  // Atualiza o display para mostrar que o aquecedor está desligado

        // Zera o timer quando o aquecedor é desligado
        heaterOnStartTime = 0;  // Reseta o timer

        // Registra no log quando o aquecedor é desligado
        logSystem.logEvent("Aquecedor foi desligado.");
    }
}

bool HeaterControl::isHeaterOn() {
    return heaterState;
}

// Variável para armazenar o tempo restante anterior
unsigned long previousTimeHeater = 0;
const float HYSTERESIS = 0.1;  // Faixa de histerese para controle fino de temperatura

void HeaterControl::update(float temperature, bool sensorError) {
    // Se houver um erro no sensor, desliga o aquecedor imediatamente
    if (sensorError) {
        turnHeaterOff();
        return;
    }

    unsigned long currentTime = millis();

    // Controle de temperatura com sobrecarga (overheat)
    if (temperature >= 25.0 + HYSTERESIS) {
        turnHeaterOff();  // Desliga o aquecedor
        overheat = true;  // Marca o estado de sobrecarga quando >= 25°C
    } else if (temperature < 22.0 - HYSTERESIS) {
        overheat = false;  // Reseta o estado de sobrecarga quando < 22°C
        turnHeaterOn();    // Liga o aquecedor se estiver muito frio
    }

    // Verifica se o aquecedor está ligado e a temperatura é exatamente 23.0°C
    if (heaterState && (temperature >= 23.0 && temperature < 23.1)) {
        // Calcula o tempo que o aquecedor já está ligado
        unsigned long timeElapsed = currentTime - heaterOnStartTime;
        unsigned long timeHeater = MAX_HEATER_ON_TIME - timeElapsed;

        // Exibe o tempo restante no display, em minutos, apenas se o tempo mudou
        int timeMinutes = timeHeater / 60000;
        static int lastTimeMinutes = -1;
        
        // Verifica se os minutos mudaram para atualizar o display
        if (timeMinutes != lastTimeMinutes) {
            display.showHeaterTime(timeMinutes); // Atualiza o display com o tempo restante em minutos
            lastTimeMinutes = timeMinutes;       // Atualiza o último valor mostrado
        }

        // Se o aquecedor estiver ligado e o tempo máximo for atingido
        if (timeElapsed > MAX_HEATER_ON_TIME) {
            turnHeaterOff();      // Desliga o aquecedor
            overheat = true;      // Marca como sobrecarga
        }
    }
}
