#include <Arduino.h>
#include <stdio.h>
#include <HX711.h>

// funçoes auxiliares
long microssegundosParaCentimetros(long microSegundos);
long leituraUnicaCM(int trigPin, int echoPin, int trigDelay, int timeout);
long lerDistanciaMediaCM(int trigPin, int echoPin, int trigDelay, int numAmostras);
void lerAmonia();
void lerPesoHX711();


/**
* @brief Mede a eficiência de leitura do sensor HC-SR04 interno (leituras por segundo).
*/
void testarEficienciaHCSR04Interno()
{
    static int leituras = 0;
    static unsigned long t0 = millis();
    lerDistanciaMediaCM(TRIG_INTERNO_PIN, ECHO_INTERNO_PIN, 10, 5);
    leituras++;
    if (millis() - t0 > 1000)
    {
        Serial.print("Leituras HC-SR04 Interno/s: ");
        Serial.println(leituras);
        leituras = 0;
        t0 = millis();
    }
}

 /**
 * @brief Mede a eficiência de leitura do sensor HC-SR04 externo (leituras por segundo).
 */
void testarEficienciaHCSR04Externo()
{
    static int leituras = 0;
    static unsigned long t0 = millis();
    lerDistanciaMediaCM(TRIG_EXTERNO_PIN, ECHO_EXTERNO_PIN, 5, 5);
    leituras++;
    if (millis() - t0 > 1000)
    {
        Serial.print("Leituras HC-SR04 Externo/s: ");
        Serial.println(leituras);
        leituras = 0;
        t0 = millis();
    }
}

/**
* @brief Mede a eficiência do sensor MQ-135 (leituras por segundo).
*/
void testarEficienciaMQ135()
{
    static int leituras = 0;
    static unsigned long t0 = millis();
    lerAmonia();
    leituras++;
    if (millis() - t0 > 1000)
    {
        Serial.print("Leituras MQ-135/s: ");
        Serial.println(leituras);
        leituras = 0;
        t0 = millis();
    }
}

/**
* @brief Mede a eficiência do sensor HX711 (leituras por segundo).
*/
void testarEficienciaHX711()
{
    static int leituras = 0;
    static unsigned long t0 = millis();
    lerPesoHX711();
    leituras++;
    if (millis() - t0 > 1000)
    {
        Serial.print("Leituras HX711/s: ");
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
