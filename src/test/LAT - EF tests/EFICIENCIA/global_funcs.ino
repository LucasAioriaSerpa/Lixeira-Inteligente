#include <Arduino.h>
#include <stdio.h>
#include <HX711.h>

// pinos necessarios para os testes
#define TRIG_INTERNO_PIN 12
#define ECHO_INTERNO_PIN 13
#define TRIG_EXTERNO_PIN 22
#define ECHO_EXTERNO_PIN 23
#define LED_VERMELHO_INTERNO_PIN 14
#define LED_AMARELO_INTERNO_PIN 26
#define LED_VERDE_INTERNO_PIN 21
#define MQ_PIN_ANALOGICO 34
#define MQ_PIN_DIGITAL 25
#define HX711_DT_PIN 18
#define HX711_SCK_PIN 19
#define HX711_FATOR_ESCALA 2280.0f

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
* @brief Mede a eficiência do sistema de LEDs (operações por segundo).
*/
void testarEficienciaLEDs()
{
    static int operacoes = 0;
    static unsigned long t0 = millis();
    
    digitalWrite(LED_VERMELHO_INTERNO_PIN, operacoes % 3 == 0);
    digitalWrite(LED_AMARELO_INTERNO_PIN, operacoes % 3 == 1);
    digitalWrite(LED_VERDE_INTERNO_PIN, operacoes % 3 == 2);
    operacoes++;
    
    if (millis() - t0 > 1000)
    {
        Serial.print("Operações LEDs/s: ");
        Serial.println(operacoes);
        operacoes = 0;
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


// funções auxiliares implementadas
long microssegundosParaCentimetros(long microSegundos) { 
    return microSegundos / 29 / 2; 
}

long leituraUnicaCM(int trigPin, int echoPin, int trigDelay, int timeout) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(trigDelay);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(trigDelay);
    digitalWrite(trigPin, LOW);
    long duracao = pulseIn(echoPin, HIGH, timeout);
    return microssegundosParaCentimetros(duracao);
}

long lerDistanciaMediaCM(int trigPin, int echoPin, int trigDelay, int numAmostras) {
    long soma = 0;
    int leiturasValidas = 0;
    for (int i = 0; i < numAmostras; i++) {
        long d = leituraUnicaCM(trigPin, echoPin, trigDelay, 30000);
        if (d > 0 && d < 400) {
            soma += d;
            leiturasValidas++;
        }
        delay(5);
    }
    return (leiturasValidas > 0) ? soma / leiturasValidas : 0;
}

void lerAmonia() {
    long soma = 0;
    const int numLeituras = 5;
    for (int i = 0; i < numLeituras; ++i) {
        soma += analogRead(MQ_PIN_ANALOGICO);
        delay(2);
    }
    analogRead(MQ_PIN_ANALOGICO); 
    digitalRead(MQ_PIN_DIGITAL);  
}

void lerPesoHX711() {
    
    for (int i = 0; i < 10; i++) { 
        digitalRead(HX711_DT_PIN);
        digitalWrite(HX711_SCK_PIN, HIGH);
        digitalWrite(HX711_SCK_PIN, LOW);
    }
}

//----------------------------------------------------------------------------------

void setup() {
    Serial.begin(9600);
    
    pinMode(TRIG_INTERNO_PIN, OUTPUT);
    pinMode(ECHO_INTERNO_PIN, INPUT);
    pinMode(TRIG_EXTERNO_PIN, OUTPUT);
    pinMode(ECHO_EXTERNO_PIN, INPUT);
    pinMode(LED_VERMELHO_INTERNO_PIN, OUTPUT);
    pinMode(LED_AMARELO_INTERNO_PIN, OUTPUT);
    pinMode(LED_VERDE_INTERNO_PIN, OUTPUT);
    pinMode(MQ_PIN_ANALOGICO, INPUT);
    pinMode(MQ_PIN_DIGITAL, INPUT);
    pinMode(HX711_DT_PIN, INPUT);
    pinMode(HX711_SCK_PIN, OUTPUT);
    
    Serial.println("Iniciando testes de eficiência...");
}

void loop() {
    testarEficienciaHCSR04Interno();
    testarEficienciaHCSR04Externo();
    testarEficienciaMQ135();
    testarEficienciaHX711();
    testarEficienciaLEDs();
    
    delay(10); 
}
