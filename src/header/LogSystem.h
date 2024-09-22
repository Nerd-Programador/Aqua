#ifndef LOGSYSTEM_H
#define LOGSYSTEM_H

#include <Arduino.h>
#include <LittleFS.h>

class LogSystem {
public:
    LogSystem(const char* logFileName);
    void begin();
    void logEvent(const String &event);
    String readLogs();
    String getLogFileName() const;  // Adiciona este método para obter o nome do arquivo de log
    
private:
    String getTimestamp();
    const char* logFileName;
    bool fsInitialized = false;  // Adiciona um indicador de inicialização
};

#endif // LOGSYSTEM_H
