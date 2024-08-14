#include <SPI.h>
#include <LoRa.h>
#include "logger.h"

#define SPI_CS    18
#define SPI_RST   16
#define SPI_SCK   5
#define SPI_MISO  19
#define SPI_MOSI  27

void setupLoRa() {
  LoRa.setPins(SPI_CS, SPI_RST, SPI_IRQ);

  if (!LoRa.begin(915E6)) {
    logError("Starting LoRa failed!");
    while (1);
  }

  // Configura parâmetros
  LoRa.setCodingRate4(5);  // Coding rate 4/5
  LoRa.setSpreadingFactor(7);  // Spreading factor 7
  LoRa.setSignalBandwidth(125E3);  // Bandwidth 125 kHz

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

  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    logInfo("Received packet with RSSI ");
    logInfo(LoRa.packetRssi());
    logInfo(" and SNR ");
    logInfo(LoRa.packetSnr());

    // Lê a mensagem recebida
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }

    logInfo("Received message");
    logSuccess(message);
  }
  
  return message; // Retorna a mensagem recebida
}