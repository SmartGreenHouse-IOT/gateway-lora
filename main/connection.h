#include <HTTPClient.h>
#include "logger.h"

// URL da API
#define API_ENDPOINT "https://api.intelligrow.tech/v1/iot/slaves/records/"
#define CONTENTOR_ENDPOINT "https://contentor.singularityleap.com/api/register_data"

void RecordData(String rx, String tx, String data) {
  HTTPClient http;
  
  logInfo("Conectando ao servidor...");
  http.begin(API_ENDPOINT);
  
  // Definir o conteúdo do payload usando as variáveis rx e tx
  String payload = "rx=" + rx + "&tx=" + tx + "&data=" + data;

  // Definir o cabeçalho content-type para application/x-www-form-urlencoded
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Enviar a requisição POST
  logInfo("Enviando dados para a API...");
  int httpResponseCode = http.POST(payload);
  
  if (httpResponseCode > 0) {
    String response = http.getString();
    logSuccess("Dados enviados com sucesso");
    logSuccess(response);
  } else {
    logError("Erro na requisição POST");
    logError(http.errorToString(httpResponseCode));
  }
  
  // Finalizar a conexão HTTP
  http.end();
  logInfo("Conexão encerrada");
}

int ContentorRecordData(float latitude, float longitude, float bateria, float volume) {
  HTTPClient http;

  logInfo("Conectando com a API...");
  http.begin(CONTENTOR_ENDPOINT);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String payload = "latitude=" + String(latitude, 6) +
                 "&longitude=" + String(longitude, 6) +
                 "&bateria=" + String(bateria, 2) +
                 "&volume=" + String(volume, 2);

  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    String response = http.getString();
    logSuccess("Dados enviados com sucesso");
    logSuccess(response);
  } else {
    logError("Erro na requisição POST");
    logError(http.errorToString(httpResponseCode));
  }

  http.end();
  logInfo("Conexão encerrada");

  return httpResponseCode;
}

void SendSensorData(const char* rx, const char* tx, int temperature, int humidity, int total_volume_ml, float flow_rate_lps, int flow_volume_ml, int soil_moisture, float light_intensity) {
  // Montar a string data com os parâmetros fornecidos
  String data = String(temperature) +
                String(humidity) +
                String(total_volume_ml) +
                String(flow_rate_lps) +
                String(flow_volume_ml) +
                String(soil_moisture) +
                String(light_intensity);

  logInfo("Dados a serem enviados: " + data);

  RecordData(rx, tx, data);
}
