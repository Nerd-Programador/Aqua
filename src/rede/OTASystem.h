#ifndef OTASYSTEM_H
#define OTASYSTEM_H

#include <ArduinoOTA.h>
#include <Arduino.h>
#include "Credentials.h"
#include "Display.h"

class OTASystem {
public:
    // Construtor da classe OTASystem
    OTASystem(const char* otaHostname, const char* otaPassword);
    
    // Inicializa o sistema OTA
    void begin();
    
    // Deve ser chamada periodicamente no loop principal para processar as atualizações OTA
    void handle();

private:
    const char* otaHostname;  // Nome do host OTA
    const char* otaPassword;  // Senha para autenticação OTA
};

#endif // OTASYSTEM_H
