#include "Display.h"

// Declaração externa do sistema de logs
extern LogSystem logSystem;

Display::Display(int width, int height) 
    : screenWidth(width), screenHeight(height), display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {}

void Display::begin() {
    Serial.println(F("Iniciando Display..."));

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }

    Serial.println(F("Display inicializado com sucesso."));
    display.clearDisplay();
    display.display();
    logSystem.logEvent("Display inicializado com sucesso.");
}

void Display::showTemperature(float temperature) {
    clearArea(0, 17, screenWidth, screenHeight - 17);

    display.setTextSize(4);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 17);

    if (isnan(temperature)) {
        display.print(F("ERRO"));
    } else {
        display.print(temperature, 1);
        display.print(F("C"));
    }

    display.display();
}

void Display::showHeaterStatus(bool isOn) {
    clearArea(80, 0, 60, 16);

    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(80, 0);
    display.print(isOn ? F("HEAT") : F("    "));

    display.display();
}

void Display::showOTAProgress(unsigned int progress, unsigned int total) {
    clearArea(0, 0, screenWidth, 16);

    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(F("Up: "));
    display.print(progress / (total / 100));
    display.println(F("%"));

    display.display();
}

void Display::showError(const char* errorMessage) {
    int16_t textWidth = strlen(errorMessage) * 12; // Ajuste conforme necessário
    int16_t startX = screenWidth;
    unsigned long previousMillis = millis();

    while (startX > -textWidth) {
        clearArea(0, 0, screenWidth, 16);

        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(startX, 0);
        display.print(errorMessage);

        display.display();

        startX -= 1; // Velocidade de rolagem

        // Controla a velocidade de rolagem sem bloquear o código
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= 50) {
            previousMillis = currentMillis;
        }
    }
}

void Display::showTemporary(const char* message, unsigned long duration) {
    clearArea(0, 0, screenWidth, 16);

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print(message);
    display.display();

    delay(duration);  // Tempo de exibição configurável
    clearArea(0, 0, screenWidth, 16);
    display.display();
}

void Display::showHeaterTime(unsigned long timeMillis) {
    // Converte o tempo restante de milissegundos para minutos
    int timeMinutes = timeMillis / 60000;

    // Limpa a área do display onde o tempo será mostrado
    clearArea(85, 50, 15, 10); // Limpa área específica para o tempo restante

    // Define o tamanho e cor do texto
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(85, 50); // Define a posição no display

    // Mostra o tempo restante em minutos
    display.print(F("T-"));
    display.print(timeMinutes);
    display.print(F("m"));

    // Atualiza o display para exibir a nova informação
    display.display();
}

void Display::clearArea(int16_t x, int16_t y, int16_t w, int16_t h) {
    display.fillRect(x, y, w, h, SSD1306_BLACK);
}
