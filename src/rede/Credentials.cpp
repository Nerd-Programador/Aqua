/*
#include "Credentials.h"

// Credenciais do Wi-Fi
String ssid = "";  // Iniciar vazia para ser preenchida pelo WiFiManager
String password = "";  // Iniciar vazia para ser preenchida pelo WiFiManager

// Configurações de IP
IPAddress local_IP;
IPAddress gateway;
IPAddress subnet;
IPAddress dns1;
IPAddress dns2;

// Credenciais OTA
const char* otaHostname = "Aquario";
const char* otaPassword = "258096";
*/

#include "Credentials.h"

// Credenciais do Wi-Fi
const char *ssid = "Seu_SSID";
const char *password = "Sua_Senha";

// Configurações de IP estático
IPAddress local_IP(192, 168, 0, 0); // Configurar o IP Static
IPAddress gateway(192, 168, 0, 0);  // Configurar o endereço Gateway conforme o roteador.
IPAddress subnet(255, 255, 255, 0);
IPAddress dns1(8, 8, 8, 8);
IPAddress dns2(8, 8, 4, 4);

// Credenciais OTA
const char* otaHostname = "Aquario";
const char* otaPassword = "258096";
