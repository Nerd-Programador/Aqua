#include <time.h>
#include <ArduinoJson.h>
#include "WebPag.h"

// Configura NTP
void setupTime() {
    // Configura o NTP com timezone e sincronização automática
    configTime(0, 0, "pool.ntp.org", "time.windows.com");

    // Define o fuso horário brasileiro de acordo com o horário de Brasília (BRT-3).
    setenv("TZ", "BRT3BRST,M10.3.0/0,M2.3.0/0", 1);

    /* // Aguarda até que o tempo seja sincronizado
    Serial.println("Sincronizando o tempo NTP...");
    int attempts = 0;
    while (time(nullptr) < 1000000000 && attempts < 30) {  // 1000000000 é o timestamp mínimo válido
        Serial.print(".");
        delay(1000);  // Aguarda 1 segundo
        attempts++;
    }

    if (attempts == 30) {
        Serial.println("Erro: Não foi possível sincronizar o tempo.");
    } else {
        Serial.println("Tempo sincronizado.");
    } */
}

// Construtor que inicializa o servidor na porta especificada e passa o nome do arquivo de log
WebPag::WebPag(uint16_t port) 
    : server(port), logSystem("/system_log.txt") {}

// Inicializa o servidor e o mDNS
void WebPag::begin() {
    if (!LittleFS.begin()) {
        Serial.println("Erro ao iniciar LittleFS!");
        return;
    }

    setupTime();  // Inicializa o NTP

    if (MDNS.begin("aquario")) {
        Serial.println("MDNS responder started");
    }

    // Configura as rotas para servir os arquivos estáticos
    server.serveStatic("/", LittleFS, "/index.html");
    server.serveStatic("/styles.css", LittleFS, "/styles.css");
    server.serveStatic("/scripts.js", LittleFS, "/scripts.js");

    // Rota para exibir logs
    server.on("/logs", std::bind(&WebPag::handleLogs, this));

    // Rota para limpar logs
    server.on("/clear-logs", HTTP_POST, [this]() {
        LittleFS.remove("/system_log.txt");
        server.send(200, "text/plain", "Logs limpos com sucesso.");
    });

    // Rota para baixar logs
    server.on("/download-log", std::bind(&WebPag::handleLogDownload, this));

    // **Nova rota para retornar a temperatura**
    server.on("/temperature", HTTP_GET, [this]() {
        float temperature = tempSensor.getTemperature();
        String tempStr = isnan(temperature) ? "Erro ao ler temperatura" : String(temperature, 2);
        if (isnan(temperature)) {
            server.send(500, "text/plain", "Erro ao ler o sensor de temperatura.");
        } else {
            server.send(200, "text/plain", tempStr);
        }
    });

    // Inicia o servidor
    server.begin();
    Serial.println("HTTP server started");

    // Rota para controle do Lumen (Ligar/Desligar)
    server.on("/toggle-lumen", HTTP_POST, [this]() {
        String body = server.arg("plain");
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, body);

        if (error) {
            server.send(400, "application/json", "{\"status\":\"erro de parse JSON\"}");
            return;
        }

        bool lumenState = doc["state"];
        if (lumenState) {
            turnOn(lumen.getStrip());  // Chama a função corretamente
            logSystem.logEvent("Lumen ligado");
        } else {
            turnOff(lumen.getStrip());  // Chama a função corretamente
            logSystem.logEvent("Lumen desligado");
        }

        server.send(200, "application/json", "{\"status\":\"ok\"}");
    });


    // **Nova rota para trocar o efeito do Lumen**
    server.on("/next-effect", HTTP_POST, [this]() {
        lumen.nextMode();
        server.send(200, "application/json", "{\"status\":\"ok\"}");
    });

    // **Nova rota para controle do Heater (Ligar/Desligar)**
    server.on("/toggle-heater", HTTP_POST, [this]() {
    String body = server.arg("plain");
    StaticJsonDocument<200> doc;

    DeserializationError error = deserializeJson(doc, body);
    if (error) {
        server.send(400, "application/json", "{\"status\":\"erro de parse JSON\"}");
        return;
    }
    bool heaterState = doc["state"];
    if (heaterState) {
        heaterControl.turnHeaterOn();  // Ligar aquecedor
        logSystem.logEvent("Aquecedor ligado manualmente.");
    } else {
        heaterControl.turnHeaterOff();  // Desligar aquecedor
        logSystem.logEvent("Aquecedor desligado manualmente.");
    }
    server.send(200, "application/json", "{\"status\":\"ok\"}");
});

    // **Nova rota para iniciar o timer do aquecedor**
    server.on("/start-timer", HTTP_POST, [this]() {
        String body = server.arg("plain");
        DynamicJsonDocument doc(200);
        deserializeJson(doc, body);
        int minutes = doc["minutes"];
        if (minutes > 0) {
            heaterTimer.start(minutes * 60000);  // Converte minutos para milissegundos
            logSystem.logEvent("Timer do aquecedor iniciado por " + String(minutes) + " minutos.");
            server.send(200, "application/json", "{\"status\":\"ok\"}");
        } else {
            server.send(400, "application/json", "{\"status\":\"invalid timer value\"}");
        }
    });

    // **Nova rota para desativar o aquecedor imediatamente (Parada de Emergência)**
    server.on("/stop-heater", HTTP_POST, [this]() {
        heaterControl.turnHeaterOff();
        heaterTimer.stop();
        logSystem.logEvent("Aquecedor desativado pela parada de emergência.");
        server.send(200, "application/json", "{\"status\":\"ok\"}");
    });
}


void WebPag::handleClient() {
    server.handleClient();  // Adicionada esta implementação
}

void WebPag::handleLogs() {
    String logs = logSystem.readLogs();
    server.send(200, "text/plain", logs);  // Envia o conteúdo do log como texto plano para a página
}

void WebPag::handleLogDownload() {
    String logFileName = logSystem.getLogFileName();
    if (LittleFS.exists(logFileName)) {
        File logFile = LittleFS.open(logFileName, "r");

        // Definir o cabeçalho HTTP para forçar o download com o nome "logs.txt"
        server.sendHeader("Content-Type", "text/plain");
        server.sendHeader("Content-Disposition", "attachment; filename=logs.txt");
        server.sendHeader("Connection", "close");

        // Enviar o arquivo
        server.streamFile(logFile, "text/plain");
        logFile.close();
    } else {
        server.send(404, "text/plain", "Arquivo de log não encontrado!");
    }
}
