#include "WiFiManagerSetup.h"

// Declaração externa do objeto Display
extern Display display;

// Construtor
WiFiManagerSetup::WiFiManagerSetup(uint8_t pin) : resetPin(pin) {
    // Inicializa o sistema de arquivos
    if (!LittleFS.begin()) {
        display.showTemporary("Falha ao montar o sistema de arquivos");
    }
    loadCredentials();  // Carrega as credenciais ao iniciar
}

// Inicializa o WiFiManager e configura o botão de reset
void WiFiManagerSetup::begin() {
    pinMode(resetPin, INPUT_PULLUP);

    wifiManager.setSaveConfigCallback(std::bind(&WiFiManagerSetup::saveConfigCallback, this)); // Configuração de callback para salvar as configurações

    if (!wifiManager.autoConnect("AquarioAP")) {
        display.showTemporary("Failed to connect, resetting");
        ESP.reset();  // Reseta o ESP se a conexão falhar
    }

    display.showTemporary("Connected to WiFi!");

    // Mostra o IP no display
    display.showTemporary(WiFi.localIP().toString().c_str());
}

// Função para verificar o status do WiFiManager e rodar a lógica do botão de reset
void WiFiManagerSetup::handle() {
    checkResetButton();
}

// Verifica se o botão foi pressionado para resetar as configurações de Wi-Fi
void WiFiManagerSetup::checkResetButton() {
    if (digitalRead(resetPin) == LOW) {
        unsigned long startTime = millis();
        while (digitalRead(resetPin) == LOW) {
            if (millis() - startTime > 5000) {  // 5000ms para evitar reset acidental
                display.showTemporary("Resetting WiFi configurations");
                Serial.println("Resetting WiFi configurations...");
                resetSettings();
                ESP.reset();
            }
        }
    }
}

// Callback para salvar as configurações de WiFi
void WiFiManagerSetup::saveConfigCallback() {
    display.showTemporary("Salvando configurações de WiFi...");
    saveCredentials(WiFi.SSID().c_str(), WiFi.psk().c_str());
}

// Salva as credenciais na memória permanente
void WiFiManagerSetup::saveCredentials(const char* ssid, const char* pass) {
    File file = LittleFS.open("/wifi_config.txt", "w");
    if (!file) {
        display.showTemporary("Falha ao abrir o arquivo para escrita");
        return;
    }

    file.println(ssid);
    file.println(pass);
    file.close();

    display.showTemporary("Configurações de WiFi salvas com sucesso!");
}

// Carrega as credenciais da memória permanente
void WiFiManagerSetup::loadCredentials() {
    File file = LittleFS.open("/wifi_config.txt", "r");
    if (!file) {
        display.showTemporary("Falha ao abrir o arquivo para leitura");
        return;
    }

    String ssid = file.readStringUntil('\n');
    String pass = file.readStringUntil('\n');
    file.close();

    ssid.trim();  // Remove espaços em branco
    pass.trim();

    if (ssid.length() > 0 && pass.length() > 0) {
        WiFi.begin(ssid.c_str(), pass.c_str());
        display.showTemporary("Tentando conectar usando credenciais salvas...");
    }
}

// Reseta as configurações de Wi-Fi
void WiFiManagerSetup::resetSettings() {
    wifiManager.resetSettings();
    display.showTemporary("Configurações WiFi resetadas!");
}
