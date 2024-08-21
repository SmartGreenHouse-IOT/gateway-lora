#include <HTTPClient.h>
#include "logger.h"

// URL da API
#define API_ENDPOINT "https://contentor.singularityleap.com/api/register_data"

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

void SendSensorData(const char* rx, const char* tx, int volume, int bateria, float latitude, float longitude, bool status) {
  // Montar a string data com os parâmetros fornecidos
  String data = String(volume) +
                String(bateria) +
                String(latitude) +
                String(longitude) +
                String(status);

  logInfo("Dados a serem enviados: " + data);

  RecordData(rx, tx, data);
}
