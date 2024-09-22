#include <Arduino.h>        // Adiciona a biblioteca Arduino.h
#include "TempSensor.h"     // Inclui o cabeçalho para manipulação do sensor de temperatura DS18B20
#include "Display.h"        // Inclui o cabeçalho para manipulação do display OLED
#include "HeaterControl.h"  // Inclui o cabeçalho para controle do aquecedor via relé
#include "OTASystem.h"      // Inclui o cabeçalho para manipulação das atualizações de Firmware
#include "Credentials.h"    // Inclui o cabeçalho com as credenciais de conexões de Wi-Fi e OTASystem
#include "Lumen.h"          // Inclui o cabeçalho para controle dos LEDs
#include "LogSystem.h"
#include "WebPag.h"
#include "Effect.h"

//#include "WiFiManagerSetup.h"

// Definições de pinos
#define TEMP_PIN    D0    // Pino do sensor DS18B20
#define SDA_PIN     D1    // Pino Verde
#define SCL_PIN     D2    // Pino Azul
#define LED_PIN     D3    // Pin onde os LEDs estão conectados
#define HEATER_PIN  D5    // Pino conectado ao relé do aquecedor
#define FAN_PIN     D6    // Pino conectado ao relé do FAN

#define BTN_LEFT    D7
#define BTN_RIGHT   D8    // Pino do botão responsável pelos LEDs RX
//#define BTN_MODE D       // Pino conectado ao ...
//#define BTN_RST D        // Pino do botão Reset das configurações Wi-Fi
#define NUM_LEDS    74     // Número de LEDs na fita


// Instancia os objetos necessários para o sistema
TempSensor tempSensor(TEMP_PIN);
Display display(SCREEN_WIDTH, SCREEN_HEIGHT);
HeaterControl heaterControl(HEATER_PIN);
OTASystem otaSystem(otaHostname, otaPassword);
LogSystem logSystem("/system_log.txt");
//WiFiManagerSetup wifiManagerSetup(BTN_RST);
Lumen lumen(NUM_LEDS, LED_PIN, BTN_RIGHT, BTN_LEFT);
Bounce btnLumen = Bounce();
WebPag webPag(80);  // Inicializa o servidor na porta 80
HeaterTimer heaterTimer;


void setup() {
    Serial.begin(115200);             // Inicializa a comunicação serial para debug
    Wire.begin(SDA_PIN, SCL_PIN);     // Inicializa a comunicação I2C para o display OLED
    logSystem.begin();
    
    display.begin();                  // Inicializa o display OLED
    tempSensor.begin();               // Inicializa o sensor de temperatura DS18B20
    heaterControl.begin();            // Inicializa o controle do aquecedor
    lumen.begin();                    // Inicializa o controle dos LEDs
    webPag.begin();                  // Inicializa o servidor web

    //wifiManagerSetup.begin();

    // Conectar ao Wi-Fi
    WiFi.begin(ssid, password);
    WiFi.config(local_IP, gateway, subnet, dns1, dns2);

    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
        delay(100);
        display.showTemporary("Connecting Wi-Fi...");
    }
    if (WiFi.status() != WL_CONNECTED) {
        display.showTemporary("Wi-Fi Connection Failed");
        // Aqui você pode implementar uma lógica de fallback, como reiniciar o ESP ou entrar em modo AP
    } else {
        display.showTemporary("Wi-Fi Connected");
    }

    otaSystem.begin();  // Inicializa o sistema OTA
    delay(500);
    logSystem.logEvent("Sistema iniciado");
}

unsigned long previousMillis = 0;  // Armazena o último tempo em que o loop foi executado
const unsigned long interval = 500;  // Intervalo de 500 milissegundos

void loop() {
    otaSystem.handle();  // Mantém o sistema OTA em funcionamento
    webPag.handleClient();  // Trata requisições do cliente

    //wifiManagerSetup.handle();

    // Verifica se o intervalo de tempo passou
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;  // Atualiza o tempo anterior com o tempo atual

        float temperature = tempSensor.getTemperature();    // Lê a temperatura atual do sensor DS18B20
        bool sensorError = isnan(temperature);              // Verifica se o sensor retornou um valor válido
        heaterControl.update(temperature, sensorError);     // Atualiza o estado do aquecedor com base na temperatura lida
        display.showTemperature(temperature);               // Exibe a temperatura lida no display OLED
    }
    lumen.update();  // Atualiza os LEDs de acordo com o modo selecionado

    // Outras tarefas que podem rodar em paralelo ao intervalo, se necessário
}

