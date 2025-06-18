#include <Arduino.h>
#include <stdio.h>

/**
 * @brief Testa a latência de leitura do sensor HC-SR04.
 * @param trigPin Pino trigger.
 * @param echoPin Pino echo.
 */
void testarLatenciaHCSR04(int trigPin, int echoPin)
{
    unsigned long t0 = micros();
    long distancia = lerDistanciaMediaCM(trigPin, echoPin, 10, 5);
    unsigned long t1 = micros();
    Serial.print("Latência HC-SR04: ");
    Serial.print(t1 - t0);
    Serial.println(" us");
}

/**
 * @brief Testa a latência de acionamento de um LED.
 * @param ledPin Pino do LED.
 */
void testarLatenciaLED(int ledPin)
{
    unsigned long t0 = micros();
    digitalWrite(ledPin, HIGH);
    unsigned long t1 = micros();
    Serial.print("Latência LED (HIGH): ");
    Serial.print(t1 - t0);
    Serial.println(" us");
    digitalWrite(ledPin, LOW);
}

/**
 * @brief Testa a latência de resposta HTTP do servidor.
 */
void testarLatenciaHTTP()
{
    unsigned long t0 = micros();
    // Simula montagem e envio de resposta
    String json = "{\"teste\":true}";
    servidor.send(200, "application/json", json);
    unsigned long t1 = micros();
    Serial.print("Latência HTTP: ");
    Serial.print(t1 - t0);
    Serial.println(" us");
}

void setup() {}

void loop() {}
