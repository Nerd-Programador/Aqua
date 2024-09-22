#include "HeaterTimer.h"
#include "HeaterControl.h"

// Declaração externa
extern HeaterControl heaterControl;
extern LogSystem logSystem;

HeaterTimer::HeaterTimer() : timerActive(false), endTime(0) {}

void HeaterTimer::start(unsigned long duration) {
    endTime = millis() + duration;
    timerActive = true;
    logSystem.logEvent("Timer do aquecedor iniciado.");
}

void HeaterTimer::stop() {
    timerActive = false;
    logSystem.logEvent("Timer do aquecedor interrompido.");
}

void HeaterTimer::update() {
    if (timerActive && millis() >= endTime) {
        heaterControl.turnHeaterOff();
        timerActive = false;
        logSystem.logEvent("Timer do aquecedor expirou e aquecedor foi desligado.");
    }
}
