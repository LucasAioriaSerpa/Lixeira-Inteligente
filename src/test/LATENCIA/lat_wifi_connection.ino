#include <WiFi.h>

const char* WIFI_SSID = "Exploda";
const char* WIFI_PASSWORD = "*******";

const char* esp_ip = "192.168.15.13"; // IP do ESP32
const uint16_t port = 80;

void setup() {
  Serial.begin(9600);

  // Calcula tempo de inicialização do módulo Wi-Fi
  unsigned long inicioWifi = millis();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando-se ao WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  unsigned long tempoWifi = millis() - inicioWifi;
  Serial.println("\nConectado ao WiFi!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("Tempo de inicialização do módulo WiFi: ");
  Serial.print(tempoWifi);
  Serial.print(" ms");
  Serial.println("");

  delay(1000);
}

void loop() {
  calcularTempoDeResposta();
  delay(10000); // Executa a cada 10 segundos
}

void calcularTempoDeResposta() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    unsigned long inicioComunicacao = millis();

    if (client.connect(esp_ip, port)) {
      // Enviar requisição GET
      client.println("GET / HTTP/1.1");
      client.println("Host: " + String(esp_ip));
      client.println("Connection: close");
      client.println();

      // Esperar resposta
      while (client.connected()) {
        if (client.available()) {
          String resposta = client.readStringUntil('\n');
          break;
        }
      }

      unsigned long tempoResposta = millis() - inicioComunicacao;
      Serial.print("Tempo de resposta para execução de tarefa: ");
      Serial.print(tempoResposta);
      Serial.print(" ms");
      Serial.println("");

      Serial.print("Tempo de comunicação entre módulos (TCP + resposta): ");
      Serial.print(tempoResposta);
      Serial.print(" ms");
      Serial.println("");

      client.stop();
    } else {
      Serial.println("Falha na conexão com o servidor!");
    }
  } else {
    Serial.println("Wi-Fi não está conectado.");
  }
}
