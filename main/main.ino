//#include "HT_SSD1306Wire.h"
#include "connection.h"
#include "wireless.h"
#include "iot_lora.h"
#include "logger.h"

// Credenciais do Wi-Fi
#define WIRELESS_SSID "SSID"
#define WIRELESS_PSWD "PSWD"

// Definição das constantes para rx e tx
#define GATEWAY_SERIAL_DEVELOPMENT "GATEWAY_SERIAL_DEVELOPMENT"
#define SLAVE_SERIAL_DEVELOPMENT "SLAVE_SERIAL_DEVELOPMENT"

void setup() {
    setupLogger(); // Inicializa o monitor serial
    setupLoRa(); // Inicializa o módulo LoRa

    // Conectar ao Wi-Fi
    connectToWiFi(WIRELESS_SSID, WIRELESS_PSWD);
}

void loop() {
    float latitude, longitude, bateria, volume;

    // Processa dados recebidos via LoRa
    if (processReceivedData(latitude, longitude, bateria, volume)) {
        // Se os dados foram processados corretamente, enviar para a API
        logInfo("Enviando dados processados para a API...");
        contentorRecordData(latitude, longitude, bateria, volume);
    } else {
        // Remover log desnecessário para evitar poluição do console
    }
    
    // Comentado para controle
    /*
    String msg = receivePacket();
    if (msg!=""){
      if (isConnectedToWiFi()) {
        sendSensorData(GATEWAY_SERIAL_DEVELOPMENT, SLAVE_SERIAL_DEVELOPMENT, 123, 456, 7890, 23.45, 6789, 234, 56.78);
        recordData(GATEWAY_SERIAL_DEVELOPMENT, SLAVE_SERIAL_DEVELOPMENT, "123456789023.45678923456.78");
      }
    }
    */
}
