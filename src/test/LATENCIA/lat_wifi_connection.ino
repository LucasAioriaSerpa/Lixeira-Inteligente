#include <Wifi.h>

const char* esp_ip = "192.168.15.13";
const uint16_t port = 80;

void calcularLatenciaWifi(){
  // Verifica se o Wi-Fi está conectado
  if (WiFi.status() == WL_CONNECTED) {
    
    WiFiClient client; // Cria um cliente WiFi (objeto que permite comunicação via TCP)
    unsigned long startTime = millis(); // Registra o tempo inicial antes da conexão

    // Tenta estabelecer conexão TCP com o IP e porta definidos
    if (client.connect(esp_ip, port)) {

      client.println("GET / HTTP/1.1"); // Envia uma requisição HTTP GET para a rota raiz "/"
      client.println("Host: " + String(esp_ip)); // Informa o cabeçalho "Host" com o IP do servidor
      client.println("Connection: close");
      client.println();

      // Enquanto a conexão estiver ativa
      while (client.connected()) { 
        // Se houver dados disponíveis para leitura
        if (client.available()) {
          String resposta = client.readStringUntil('\n'); // Lê a primeira linha da resposta
          break; // Sai do loop após receber uma resposta
        }
      }

      // Exibe a latência no monitor serial
      unsigned long latencia = millis() - startTime;
      Serial.print("Latência Wi-Fi: ");
      Serial.print(latencia);
      Serial.print(" ms");
      Serial.println("");

      client.stop();
    } else {
      Serial.println("Falha na conexão!");
    }
  } else {
    Serial.println("Wi-Fi não conectado!");
  }
}

void loop() {
  calcularLatenciaWifi();
  delay(10000); // Mede a cada 10 segundos
}
