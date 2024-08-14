#include <WiFi.h>
#include "logger.h"

// Função para conectar ao Wi-Fi
void connectToWiFi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    logInfo("Conectando ao Wi-Fi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        logInfo("Aguardando conexão...");
    }
    logSuccess("Conectado ao Wi-Fi");
}

bool isConnectedToWiFi() {
    if (WiFi.status() == WL_CONNECTED) {
        logSuccess("Conectado ao Wi-Fi");
    } else {
        logError("Sem conexão Wi-Fi");
    }
    return WiFi.status() == WL_CONNECTED;
}
