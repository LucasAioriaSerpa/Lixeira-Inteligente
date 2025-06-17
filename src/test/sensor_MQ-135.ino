#include <Arduino.h>

#define MQ_ANALOG_PIN 33  // ADC-capable pin (ESP32: 32-39)
#define MQ_DIGITAL_PIN 25 // Digital-capable pin

void setup() {
  Serial.begin(9600);
  pinMode(MQ_DIGITAL_PIN, INPUT);
}

void loop() {
  int analogValue = analogRead(MQ_ANALOG_PIN);
  bool gasDetected = digitalRead(MQ_DIGITAL_PIN) == LOW;

  Serial.print(analogValue);
  Serial.print(" || ");
  Serial.println(gasDetected ? "GAS DETECTADO !!!" : "GAS AUSENTE !!!");
  delay(500);
}
