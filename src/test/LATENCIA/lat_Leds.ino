#include <Arduino.h>

// Definição dos pinos
const int GREEN_LED = 14;
const int YELLOW_LED = 27;
const int RED_LED = 26;

// Estrutura para representar um LED
struct Led {
  const char* color;
  int pin;
};

Led leds[] = {
  {"VERDE", GREEN_LED},
  {"AMARELO", YELLOW_LED},
  {"VERMELHO", RED_LED}
};

// Função para acender e apagar um LED e medir tempo de resposta da tarefa
void onOffLed(const Led& led) {
  unsigned long start = millis(); // Tempo antes de acender

  Serial.print("LED -> ");
  Serial.println(led.color);
  digitalWrite(led.pin, HIGH);

  delay(50); // Simula tempo perceptível

  digitalWrite(led.pin, LOW);

  unsigned long end = millis(); // Tempo após apagar
  Serial.print("Tempo de resposta para execução de tarefa (ms): ");
  Serial.println(end - start);
}

unsigned long initStart, initEnd;

void setup() {
  initStart = millis(); // Tempo inicio

  Serial.begin(9600);

  // Configura os pinos como saída
  for (auto& led : leds) {
    pinMode(led.pin, OUTPUT);
  }

  initEnd = millis(); // Tempo fim
  Serial.print("Tempo de inicialização do módulo (ms): ");
  Serial.println(initEnd - initStart);
}

void loop() {
  for (int i = 0; i < 3; i++) {
    // Simula tempo de comunicação entre módulos
    unsigned long commStart = millis();
    delay(10); // Simulação de delay de comunicação
    unsigned long commEnd = millis();

    Serial.print("Tempo de comunicação entre módulos (ms): ");
    Serial.println(commEnd - commStart);

    // Tempo de processamento
    unsigned long procStart = millis();
    onOffLed(leds[i]);
    unsigned long procEnd = millis();

    Serial.print("Tempo de processamento de dados recebidos (ms): ");
    Serial.println(procEnd - procStart);

    delay(1000); // Aguarda 1 segundo antes de passar para o próximo LED
  }

  // Após os 3 LEDs, o loop para 
  while (true);
}
