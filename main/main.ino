#include "HT_SSD1306Wire.h"
#include "logger.h"
#include "connection.h"
#include "wireless.h"
#include "lora.h"

// Configuração do Display OLED
SSD1306Wire factory_display(0x3c, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);

// Credenciais do Wi-Fi
#define WIRELESS_SSID "WIRELESS_SSID"
#define WIRELESS_PSWD "WIRELESS_PSWD"

// Definição das constantes para rx e tx
#define GATEWAY_SERIAL_DEVELOPMENT "GATEWAY_SERIAL_DEVELOPMENT"
#define SLAVE_SERIAL_DEVELOPMENT "SLAVE_SERIAL_DEVELOPMENT"

void setup() {
    setupLogger(); // Inicializa o logger e o display
    setupLoRa();

    // Conectar ao Wi-Fi
    connectToWiFi(WIRELESS_SSID, WIRELESS_PSWD);
}

void loop() {
    String msg = receivePacket()
    if (isConnectedToWiFi()) {
        // SendSensorData(GATEWAY_SERIAL_DEVELOPMENT, SLAVE_SERIAL_DEVELOPMENT, 123, 456, 7890, 23.45, 6789, 234, 56.78);
        // RecordData(GATEWAY_SERIAL_DEVELOPMENT, SLAVE_SERIAL_DEVELOPMENT, "123456789023.45678923456.78");
    }
    delay(100);
}
