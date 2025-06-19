#include <Arduino.h>

// Pinos
#define MQ_ANALOG_PIN 33   
#define MQ_DIGITAL_PIN 25  

unsigned long startInitTime, endInitTime;
bool sensorPronto = false;

void setup() {
  Serial.begin(9600);
  pinMode(MQ_DIGITAL_PIN, INPUT);

  startInitTime = millis();
  delay(20000); // MQ-135 exige ~20s para aquecimento
  endInitTime = millis();
  sensorPronto = true;

  Serial.print("Tempo de inicialização do módulo (ms): ");
  Serial.println(endInitTime - startInitTime);
}

void loop() {
  // Tempo de resposta para execução da leitura
  unsigned long startReadTime = millis();
  int analogValue = analogRead(MQ_ANALOG_PIN);
  bool gasDetected = digitalRead(MQ_DIGITAL_PIN) == LOW;
  unsigned long endReadTime = millis();

  unsigned long tempoResposta = endReadTime - startReadTime;

  // Tempo de comunicação entre módulos (simulação com Serial)
  unsigned long startCommTime = millis();
  Serial.print("Valor analógico: ");
  Serial.print(analogValue);
  Serial.print(" || ");
  Serial.print(gasDetected ? "GAS DETECTADO !!!" : "GAS AUSENTE !!!");
  unsigned long endCommTime = millis();
  unsigned long tempoComunicacao = endCommTime - startCommTime;

  // Tempo de processamento (simples)
  unsigned long startProcTime = millis();
  if (analogValue > 400 || gasDetected) {
    // simulação de processamento
    delay(10);
  }
  unsigned long endProcTime = millis();
  unsigned long tempoProcessamento = endProcTime - startProcTime;

  // Exibir todos os tempos medidos
  Serial.print(" || Tempo de resposta (ms): ");
  Serial.print(tempoResposta);

  Serial.print(" || Tempo de comunicação (ms): ");
  Serial.print(tempoComunicacao);

  Serial.print(" || Tempo de processamento (ms): ");
  Serial.println(tempoProcessamento);

  delay(1000);
}
