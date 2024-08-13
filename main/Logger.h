#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include "HT_SSD1306Wire.h"

// Variável global para o display
extern SSD1306Wire factory_display;

void setupLogger() {
    Serial.begin(115200);
    factory_display.init();
    factory_display.clear();
    factory_display.display();
}

void logMessage(String level, String message) {
    String logMessage = level + " " + message;
    Serial.println(logMessage);
    factory_display.clear();
    factory_display.drawString(0, 0, logMessage);
    factory_display.display();
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
