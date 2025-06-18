#include <Arduino.h>
#include <stdio.h>

/**
 * @brief Mede a eficiência de leitura do sensor HC-SR04 (leituras por segundo).
 * @param trigPin Pino trigger.
 * @param echoPin Pino echo.
 */
void testarEficienciaHCSR04(int trigPin, int echoPin)
{
    static int leituras = 0;
    static unsigned long t0 = millis();
    lerDistanciaMediaCM(trigPin, echoPin, 10, 5);
    leituras++;
    if (millis() - t0 > 1000)
    {
        Serial.print("Leituras HC-SR04/s: ");
        Serial.println(leituras);
        leituras = 0;
        t0 = millis();
    }
}

/**
 * @brief Mede a eficiência do servidor HTTP (requisições por segundo).
 *        Chame em handleRoot().
 */
void testarEficienciaHTTP()
{
    static int reqs = 0;
    static unsigned long t0 = millis();
    reqs++;
    if (millis() - t0 > 1000)
    {
        Serial.print("Requisições HTTP/s: ");
        Serial.println(reqs);
        reqs = 0;
        t0 = millis();
    }
}

void setup() {}

void loop() {}
