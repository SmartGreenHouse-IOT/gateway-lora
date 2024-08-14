#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include "HT_SSD1306Wire.h"

// Variável global para o display
extern SSD1306Wire factory_display;
int currentLine = 0; // Variável global para controlar a linha atual do display

void setupLogger() {
    Serial.begin(115200);
    factory_display.init();
    factory_display.clear();
    factory_display.display();
    currentLine = 0; // Inicializa a posição da linha
}

void logMessage(String level, String message) {
    String logMessage = level + " " + message;
    Serial.println(logMessage);

    // Limpa o display se a linha estiver fora dos limites
    if (currentLine >= factory_display.getHeight()) {
        factory_display.clear();
        currentLine = 0;
    }

    factory_display.drawString(0, currentLine, logMessage);
    factory_display.display();

    // Incrementa a posição para a próxima linha
    currentLine += 10; // Ajuste o valor conforme necessário para a altura do texto
}

void logInfo(String message) {
    logMessage("[INFO]", message);
}

void logError(String message) {
    logMessage("[ERROR]", message);
}

void logSuccess(String message) {
    logMessage("[OK]", message);
}

#endif
