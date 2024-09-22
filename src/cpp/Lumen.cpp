#include "Lumen.h"

// Declaração externa do objeto Display
extern Display display;
// Declaração externa do sistema de logs
extern LogSystem logSystem;

Lumen::Lumen(int numLeds, int ledPin, int btnRightPin, int btnLeftPin)
    : strip(numLeds, ledPin, NEO_GRB + NEO_KHZ800), 
    btnRightPin(btnRightPin), btnLeftPin(btnLeftPin),
    btnRight(), btnLeft() {
        strip.updateLength(numLeds);  // Garante que o número correto de LEDs seja configurado
    }

// Retorna o objeto strip (Adafruit_NeoPixel)
Adafruit_NeoPixel& Lumen::getStrip() {
    return strip;
}

void Lumen::begin() {
    // Configuração inicial do strip de LEDs
    strip.begin();
    strip.show();  // Inicializa todos os LEDs apagados
    strip.setBrightness(250);  // Configura o brilho inicial (ajuste conforme necessário)

    btnLeft.attach(btnLeftPin, INPUT_PULLUP);
    btnRight.attach(btnRightPin, INPUT_PULLUP);
}

void Lumen::nextMode() {
    currentMode = (currentMode + 1) % NUM_MODES;
    showFeedback();
}

void Lumen::previousMode() {
    currentMode = (currentMode - 1) % NUM_MODES;
    showFeedback();
}

void Lumen::applyMode() {
    switch (currentMode) {
        case OFF:
            turnOff(strip);  // Desliga os LEDs, apenas uma vez
            break;
        case ON:
            turnOn(strip);  // Mantém os LEDs ligados, sem necessidade de chamar repetidamente
            break;
        case BINARY_RGB:
            binaryRGB(strip);  // Certifique-se de que esta função mantém o efeito
            break;
        case PLANT_GROWTH:
            plantGrowth(strip);  // Certifique-se de que esta função mantém o efeito
            break;
        case RAINBOW_CYCLE:
            rainbowCycle(strip);  // Certifique-se de que esta função mantém o efeito
            break;
        case DAY_NIGHT_CYCLE:
            dayNightCycle(strip);  // Certifique-se de que esta função mantém o efeito
            break;
        case MOONLIGHT_EFFECT:
            moonlightEffect(strip);  // Certifique-se de que esta função mantém o efeito
            break;
    }
}

void Lumen::showFeedback() {
    switch (currentMode) {
        case OFF:
            display.showTemporary("Off");
            logSystem.logEvent("Off");
            break;
        case ON:
            display.showTemporary("On");
            logSystem.logEvent("On");
            break;
        case BINARY_RGB:
            display.showTemporary("BinaryRGB");
            logSystem.logEvent("BinaryRGB");
            break;
        case PLANT_GROWTH:
            display.showTemporary("PlantGrowth");
            logSystem.logEvent("PlantGrowth");
            break;
        case RAINBOW_CYCLE:
            display.showTemporary("Rainbow");
            logSystem.logEvent("Rainbow");
            break;
        case DAY_NIGHT_CYCLE:
            display.showTemporary("Day-Night");
            logSystem.logEvent("Day-Night");
            break;
        case MOONLIGHT_EFFECT:
            display.showTemporary("Moonlight");
            logSystem.logEvent("MoonLight");
            break;
    }
}

void Lumen::handleButtons() {
    const unsigned long debounceDelay = 50;  // 50 ms de debounce

    static unsigned long lastPressTimeLeft = 0;
    static unsigned long lastPressTimeRight = 0;

    btnLeft.update();
    btnRight.update();

    unsigned long now = millis();

    if (btnLeft.fell() && (now - lastPressTimeLeft > debounceDelay)) {
        nextMode();
        lastPressTimeLeft = now;  // Atualiza o último tempo do botão esquerdo
        logSystem.logEvent("Botão Left pressionado");
    }

    if (btnRight.fell() && (now - lastPressTimeRight > debounceDelay)) {
        previousMode();
        lastPressTimeRight = now;  // Atualiza o último tempo do botão direito
        logSystem.logEvent("Botão Right pressionado");
    }
}

void Lumen::update() {
    handleButtons();

    // Aplica o modo atual (executa o efeito de LED correspondente)
    applyMode();
}
