#ifndef WEBPAG_H
#define WEBPAG_H

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "LogSystem.h"
#include "Credentials.h"
#include "OTASystem.h"
#include "Display.h"
#include "HeaterControl.h"
#include "TempSensor.h"
#include "Lumen.h"
#include "HeaterTimer.h"
#include "Effect.h"

class WebPag {
public:
    WebPag(uint16_t port);  // Construtor que permite definir a porta do servidor
    
    void begin();  // Inicializa o servidor e o mDNS
    void handleClient();  // Função para ser chamada no loop principal para tratar as requisições

private:
    ESP8266WebServer server;  // Objeto servidor
    LogSystem logSystem;  // Instância do sistema de logs
    File fsUploadFile;  // Arquivo para upload
    HeaterTimer heaterTimer;  // Declara a variável heaterTimer aqui

    void handleLogs();  // Método para lidar com requisições à URL /logs
    void handleFileUpload();  // Nova função para lidar com upload de arquivos
    void handleLogDownload();  // Nova função para lidar com o download do log
};

// Declaração externa dos objetos para serem usados dentro do WebPag
extern TempSensor tempSensor;  // Objeto do sensor de temperatura
extern HeaterControl heaterControl;  // Objeto do controle do aquecedor
extern Lumen lumen;  // Objeto do controle dos LEDs
extern HeaterTimer heaterTimer;  // Objeto do timer do aquecedor

#endif // WEBPAG_H
