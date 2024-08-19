#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>


void setupLogger() {
    Serial.begin(115200); //inicia o monitor serial
}

void logMessage(String level, String message) {
    String logMessage = level + " " + message;
    Serial.println(logMessage); // Ajuste o valor conforme necessário para a altura do texto
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
