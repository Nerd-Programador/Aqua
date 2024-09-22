#include "LogSystem.h"

LogSystem::LogSystem(const char* logFileName) : logFileName(logFileName) {}

void LogSystem::begin() {
    if (!LittleFS.begin()) {
        Serial.println("Erro ao iniciar LittleFS!");
        logEvent("Erro ao iniciar LittleFS! Sistema de arquivos não disponível.");
        fsInitialized = false;  // Marca como não inicializado
    } else {
        Serial.println("LittleFS inicializado com sucesso!");
        logEvent("LittleFS inicializado com sucesso.");
        fsInitialized = true;
    }

    // Verifica se o arquivo de log já existe
    if (fsInitialized && !LittleFS.exists("/system_log.txt")) {
        File logFile = LittleFS.open("/system_log.txt", "w");
        if (logFile) {
            logFile.close();
            Serial.println("Arquivo de log criado.");
        } else {
            Serial.println("Falha ao criar o arquivo de log.");
        }
    }
}

void LogSystem::logEvent(const String &event) {
    if (!fsInitialized) {
        Serial.println("LittleFS não foi inicializado, log não registrado.");
        return;
    }

    File logFile = LittleFS.open(logFileName, "a");  // "a" para adicionar ao final do arquivo
    if (!logFile) {
        Serial.println("Erro ao abrir o arquivo de log!");
        return;
    }
    String logEntry = getTimestamp() + " - " + event + "\n";
    logFile.print(logEntry);
    logFile.close();
}

String LogSystem::readLogs() {
    if (!fsInitialized) {
        return "LittleFS não foi inicializado!";
    }

    File logFile = LittleFS.open(logFileName, "r");  // Abre o arquivo de log para leitura
    if (!logFile) {
        return "Erro ao abrir o arquivo de log!";
    }
    
    String logs = logFile.readString();  // Lê todo o conteúdo do arquivo de log
    logFile.close();
    return logs;  // Retorna o conteúdo do log como uma string
}

String LogSystem::getLogFileName() const {
    return String(logFileName);
}

String LogSystem::getTimestamp() {
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d/%m/%y - %H:%M:%S", timeinfo);  // Formato 24h
    return String(buffer);
}
