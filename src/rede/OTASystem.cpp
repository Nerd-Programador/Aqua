#include "OTASystem.h"

// Declaração externa do objeto Display
extern Display display;

// Construtor que inicializa o hostname e a senha OTA
OTASystem::OTASystem(const char* hostname, const char* password)
    : otaHostname(hostname), otaPassword(password) {}

void OTASystem::begin() {
    // Configura o nome do host OTA (aparece na rede quando buscando dispositivos)
    ArduinoOTA.setHostname(otaHostname);

    // Configura a senha OTA para proteção
    ArduinoOTA.setPassword(otaPassword);

    // Define o que acontece quando uma atualização OTA começa
    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
            type = "sketch";
        } else {  // U_SPIFFS
            type = "filesystem";
        }
        // Exibe uma mensagem no console sobre o início da atualização
        Serial.println("Starting update: " + type);
    });

    // Define o que acontece durante o progresso da atualização OTA
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        display.showOTAProgress(progress, total);  // Atualiza o display com o progresso
    });

    // Define o que acontece quando uma atualização OTA termina
    ArduinoOTA.onEnd([]() {
        Serial.println("\nAtualização finalizada!");
        display.showTemporary("Success!");
    });

    // Define o que acontece se ocorrer um erro durante a atualização OTA
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Erro [%u]: ", error);
        if (error == OTA_AUTH_ERROR) {
            Serial.println("Falha na autenticação");
            display.showError("Falha na autent.");
        } else if (error == OTA_BEGIN_ERROR) {
            Serial.println("Erro ao iniciar a atualiz.");
            display.showError("Erro no inicio.");
        } else if (error == OTA_CONNECT_ERROR) {
            Serial.println("Erro de conexão");
            display.showError("Erro de conexão");
        } else if (error == OTA_RECEIVE_ERROR) {
            Serial.println("Erro ao receber dados");
            display.showError("Erro ao receber");
        } else if (error == OTA_END_ERROR) {
            Serial.println("Erro ao finalizar a atualiz.");
            display.showError("Erro ao finalizar");
        }
    });

    // Inicia o serviço OTA
    ArduinoOTA.begin();
}

void OTASystem::handle() {
    // Mantém o serviço OTA em funcionamento, deve ser chamado no loop principal
    ArduinoOTA.handle();
}
