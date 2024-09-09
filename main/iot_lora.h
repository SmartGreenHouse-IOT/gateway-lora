#include <SPI.h>
#include <LoRa.h>
#include "logger.h"

#define SPI_CS 18
#define SPI_RST 14
#define SPI_IRQ 26
#define SPI_SCK 5
#define SPI_MISO 19
#define SPI_MOSI 27

// Variável global para armazenar o último pacote recebido
String lastReceivedMessage = "";

void setupLoRa() {
  LoRa.setPins(SPI_CS, SPI_RST, SPI_IRQ); // Pinagem necessária para o módulo funcionar

  if (!LoRa.begin(915E6)) { // 915MHz = frequência de operação do módulo LoRa
    logError("Falha ao iniciar LoRa!");
    while (1);
  }

  // Configura parâmetros
  LoRa.setCodingRate4(5);          // Coding rate 4/5
  LoRa.setSpreadingFactor(7);      // Spreading factor 7
  LoRa.setSignalBandwidth(125E3);  // Bandwidth 125 kHz

  LoRa.receive(); // Coloca o módulo em estado de recepção

  logSuccess("Inicialização do LoRa bem-sucedida.");
}

String receive_Packet() {
  String message = "";
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    logInfo("Pacote recebido com tamanho: " + String(packetSize));
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }
  }
  
  return message; 
}

bool isSameData(const String& newMessage) {
    if (newMessage == lastReceivedMessage) {
        logInfo("Mensagem duplicada recebida, ignorando...");
        return true;  // Indica que o dado é o mesmo
    }
    lastReceivedMessage = newMessage;  // Atualiza para o novo pacote recebido
    return false;
}

bool processReceivedData(float& latitude, float& longitude, float& bateria, float& volume) {
    String msg = receive_Packet();
    if (msg != "") {
        if (isSameData(msg)) {
            return false;  // Ignora o processamento se o dado for o mesmo
        }


    }
}
