#include <SPI.h>
#include "logger.h"
#include "heltec.h"  // Certifique-se de incluir a biblioteca Heltec

#define SPI_CS 18
#define SPI_RST 14
#define SPI_IRQ 26
#define SPI_SCK 5
#define SPI_MISO 19
#define SPI_MOSI 27

void setupLoRa() {
  LoRa.setPins(SPI_CS, SPI_RST, SPI_IRQ);

  // Configura a frequência e ativa o PABOOST (true)
  if (!LoRa.begin(915E6, false)) {
    logError("Starting LoRa failed!");
    while (1);
  }

  // Configura parâmetros
  LoRa.setCodingRate4(5);  // Coding rate 4/5
  LoRa.setSpreadingFactor(7);  // Spreading factor 7
  LoRa.setSignalBandwidth(125E3);  // Bandwidth 125 kHz

  LoRa.receive();

  logSuccess("LoRa Initialization successful.");
}

void sendPacket() {
  LoRa.beginPacket();
  LoRa.print("Hello");
  LoRa.endPacket();
  logInfo("Pacote LoRa enviado...");
}

String receivePacket() {
  String message = "";

  // logInfo("Waiting for Packet");
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    logInfo("Received packet with RSSI and SNR");

    // Lê a mensagem recebida
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }

    logInfo("Received message");
    logSuccess(message);
  }
  
  return message; // Retorna a mensagem recebida
}