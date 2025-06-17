#include <Arduino.h>

const int maxRange = 30;
const int minRange = 5;

const int TRIG = 22; // ? 22 FORA // dentro 12
const int ECHO = 23; // ? 23 FORA // dentro 13

// Funções inline para conversão, otimizando chamadas
inline long microSecondsToInches(long microSeconds) { return microSeconds / 74 / 2; }
inline long microSecondsToCentimeters(long microSeconds) { return microSeconds / 29 / 2; }

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  // Usa unsigned long para maior precisão
  unsigned long duration;

  // Garante pulso limpo no TRIG
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 30000); // timeout para evitar travamento

  // Só processa se recebeu eco
  if (duration > 0) {
    long inches = microSecondsToInches(duration);
    long cm = microSecondsToCentimeters(duration);

    Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
  } else {
    Serial.println("Sem resposta do sensor");
  }

  delay(100);
}
