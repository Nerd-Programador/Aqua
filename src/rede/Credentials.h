/*
#ifndef Credentials_h
#define Credentials_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <IPAddress.h>

// Credenciais do Wi-Fi (deixar vazias para serem preenchidas pelo WiFiManager)
extern String ssid;
extern String password;

// Configurações de IP (deixar vazias para serem preenchidas pelo WiFiManager)
extern IPAddress local_IP;
extern IPAddress gateway;
extern IPAddress subnet;
extern IPAddress dns1;
extern IPAddress dns2;

// Credenciais OTA
extern const char* otaHostname;
extern const char* otaPassword;

#endif
*/

#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

extern const char* ssid;
extern const char* password;
extern const char* otaHostname;
extern const char* otaPassword;
extern IPAddress local_IP;
extern IPAddress gateway;
extern IPAddress subnet;
extern IPAddress dns1;
extern IPAddress dns2;

#endif
