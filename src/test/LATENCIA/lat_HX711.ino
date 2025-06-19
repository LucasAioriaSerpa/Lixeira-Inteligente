#include <Arduino.h>
#include "HX711.h"

// Configuração dos pinos e fator de escala do sensor HX711

constexpr int DT_PIN = 14; // Pino DT (Data)
constexpr int SCK_PIN = 12; // Pino SCK (Clock)
constexpr float SCALE_FACTOR = 2280.0f; // Fator de escala do sensor

HX711 scale;

void setup() {
  Serial.begin(9600);

  unsigned long startInit = millis();
  Serial.println(F("HX711 teste de escala\nIniciando a escala..."));

  scale.begin(DT_PIN, SCK_PIN);
  delay(1000);  // Estabilização do sensor

  scale.set_scale(SCALE_FACTOR);

  // Marca o tempo de início e fim do processo de tara (zerar o peso)
  unsigned long tareStart = millis();
  scale.tare(); // Zera a balança
  unsigned long tareEnd = millis();

  unsigned long initEnd = millis();

  Serial.println(F("Scale initialized"));

  Serial.printf("Tempo de inicialização do módulo: %lu ms\n", initEnd - startInit);
  Serial.printf("Tempo de tare (calibração inicial): %lu ms\n", tareEnd - tareStart);
}

void loop() {
  // Tempo de resposta: leitura bruta
  unsigned long startReadRaw = millis();
  long raw = scale.read_average(1);
  unsigned long endReadRaw = millis();

  // Tempo de processamento: conversão de valor bruto para peso
  unsigned long startProcessing = millis();
  float weight = scale.get_units(1);
  unsigned long endProcessing = millis();

  // Tempo de comunicação simulada: envio para outra tarefa (ex: Serial)
  unsigned long startComm = millis();
  Serial.printf("Raw: %ld | Weight: %.1f\n", raw, weight);
  unsigned long endComm = millis();

  Serial.printf("Tempo de resposta para leitura: %lu ms\n", endReadRaw - startReadRaw);
  Serial.printf("Tempo de processamento do valor: %lu ms\n", endProcessing - startProcessing);
  Serial.printf("Tempo de comunicação (Serial): %lu ms\n", endComm - startComm);
  Serial.println("");

  delay(1000);
}
