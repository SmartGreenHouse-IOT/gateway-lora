#include <SPI.h>
#include <LoRa.h>
#include "logger.h"

#define SPI_CS 18
#define SPI_RST 14
#define SPI_IRQ 26
#define SPI_SCK 5
#define SPI_MISO 19
#define SPI_MOSI 27

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

}

String receive_Packet() { //função para ler de fato os dados que chegaram
  String message = "";

  int packetSize = LoRa.parsePacket(); //função para verificar se há pacote recebido, se houver, le a mensagem do pacote e retorna o tamanho do pacote. Se não houver, retorna 0.
  if (packetSize) {
    logInfo("Received packet with RSSI and SNR");


    while (LoRa.available()) { //LoRa.available verifica se há dados no buffer do módulo LoRa
      message += (char)LoRa.read(); //dados são passados para char e armazenados na variável message
    }
    logInfo("Received message");
    logSuccess(message);
  }
  
  return message; // Retorna a mensagem recebida
}
