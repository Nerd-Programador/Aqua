#ifndef WiFiManagerSetup_h
#define WiFiManagerSetup_h

#include <Arduino.h>
#include <WiFiManager.h>
#include <LittleFS.h>
#include "Credentials.h"
#include "Display.h"

// Declaração da classe
class WiFiManagerSetup {
public:
    WiFiManagerSetup(uint8_t pin);
    void begin();
    void handle();  // Para manter o WiFiManager rodando
    bool isConnected();
    void resetSettings();

private:
    WiFiManager wifiManager;
    uint8_t resetPin;
    void checkResetButton();  // Função para checar o botão de reset

    // Funções para salvar e carregar as credenciais
    void saveCredentials(const char* ssid, const char* pass);
    void loadCredentials();
    void saveConfigCallback();  // Callback para salvar as configurações
};

#endif
