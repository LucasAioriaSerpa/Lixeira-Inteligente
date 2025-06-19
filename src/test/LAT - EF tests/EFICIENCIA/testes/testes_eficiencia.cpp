#include "testes_eficiencia.h"
#include "../sensores/hc_sr04.h"
#include "../sensores/mq135.h"
#include "../sensores/hx711.h"
#include "../atuadores/leds.h"
#include "../conexao/server.h"

// Variáveis estáticas para contagem de operações
static int leiturasHC_SR04Interno = 0;
static int leiturasHC_SR04Externo = 0;
static int leiturasMQ135 = 0;
static int leiturasHX711 = 0;
static int operacoesLED = 0;
static int requisicoesHTTP = 0;

// Timers para medição de 1 segundo
static unsigned long timerHC_SR04Interno = 0;
static unsigned long timerHC_SR04Externo = 0;
static unsigned long timerMQ135 = 0;
static unsigned long timerHX711 = 0;
static unsigned long timerLED = 0;
static unsigned long timerHTTP = 0;

void executarTestesEficiencia() {
    testarEficienciaHCSR04Interno();
    testarEficienciaHCSR04Externo();
    testarEficienciaMQ135();
    testarEficienciaHX711();
    testarEficienciaLEDs();
    // testarEficienciaHTTP() é chamado dentro de handleRoot()
}

void testarEficienciaHCSR04Interno() {
    static bool primeiraLeitura = true;
    
    if (primeiraLeitura) {
        timerHC_SR04Interno = millis();
        primeiraLeitura = false;
    }
    
    // Simula a leitura sem afetar o sistema principal
    lerDistanciaMediaCM(TRIG_INTERNO_PIN, ECHO_INTERNO_PIN);
    leiturasHC_SR04Interno++;
    
    if (millis() - timerHC_SR04Interno > 1000) {
        Serial.print("[TESTE] HC-SR04 Interno: ");
        Serial.print(leiturasHC_SR04Interno);
        Serial.println(" leituras/s");
        leiturasHC_SR04Interno = 0;
        timerHC_SR04Interno = millis();
    }
}

void testarEficienciaHCSR04Externo() {
    static bool primeiraLeitura = true;
    
    if (primeiraLeitura) {
        timerHC_SR04Externo = millis();
        primeiraLeitura = false;
    }
    
    lerDistanciaMediaCM(TRIG_EXTERNO_PIN, ECHO_EXTERNO_PIN);
    leiturasHC_SR04Externo++;
    
    if (millis() - timerHC_SR04Externo > 1000) {
        Serial.print("[TESTE] HC-SR04 Externo: ");
        Serial.print(leiturasHC_SR04Externo);
        Serial.println(" leituras/s");
        leiturasHC_SR04Externo = 0;
        timerHC_SR04Externo = millis();
    }
}

void testarEficienciaMQ135() {
    static bool primeiraLeitura = true;
    
    if (primeiraLeitura) {
        timerMQ135 = millis();
        primeiraLeitura = false;
    }
    
    // Simulação da leitura sem afetar valores reais
    analogRead(MQ_PIN_ANALOGICO);
    digitalRead(MQ_PIN_DIGITAL);
    leiturasMQ135++;
    
    if (millis() - timerMQ135 > 1000) {
        Serial.print("[TESTE] MQ-135: ");
        Serial.print(leiturasMQ135);
        Serial.println(" leituras/s");
        leiturasMQ135 = 0;
        timerMQ135 = millis();
    }
}

void testarEficienciaHX711() {
    static bool primeiraLeitura = true;
    
    if (primeiraLeitura) {
        timerHX711 = millis();
        primeiraLeitura = false;
    }
    
    // Simulação da leitura
    digitalRead(HX711_DT_PIN);
    digitalWrite(HX711_SCK_PIN, HIGH);
    digitalWrite(HX711_SCK_PIN, LOW);
    leiturasHX711++;
    
    if (millis() - timerHX711 > 1000) {
        Serial.print("[TESTE] HX711: ");
        Serial.print(leiturasHX711);
        Serial.println(" leituras/s");
        leiturasHX711 = 0;
        timerHX711 = millis();
    }
}

void testarEficienciaLEDs() {
    static bool primeiraOperacao = true;
    
    if (primeiraOperacao) {
        timerLED = millis();
        primeiraOperacao = false;
    }
    
    // Ciclo rápido de teste sem afetar o estado real
    digitalWrite(LED_VERMELHO_INTERNO_PIN, operacoesLED % 3 == 0);
    digitalWrite(LED_AMARELO_INTERNO_PIN, operacoesLED % 3 == 1);
    digitalWrite(LED_VERDE_INTERNO_PIN, operacoesLED % 3 == 2);
    operacoesLED++;
    
    if (millis() - timerLED > 1000) {
        Serial.print("[TESTE] LEDs: ");
        Serial.print(operacoesLED);
        Serial.println(" operações/s");
        operacoesLED = 0;
        timerLED = millis();
        
        // Restaura estado original
        digitalWrite(LED_VERMELHO_INTERNO_PIN, LOW);
        digitalWrite(LED_AMARELO_INTERNO_PIN, LOW);
        digitalWrite(LED_VERDE_INTERNO_PIN, LOW);
    }
}

void testarEficienciaHTTP() {
    static bool primeiraRequisicao = true;
    
    if (primeiraRequisicao) {
        timerHTTP = millis();
        primeiraRequisicao = false;
    }
    
    requisicoesHTTP++;
    
    if (millis() - timerHTTP > 1000) {
        Serial.print("[TESTE] HTTP: ");
        Serial.print(requisicoesHTTP);
        Serial.println(" requisições/s");
        requisicoesHTTP = 0;
        timerHTTP = millis();
    }
}

/**
Como usar:

Para testes contínuos:
void loop() {
    executarTestesEficiencia();
    delay(10);
}

Para teste específico (ex: HTTP):
void handleRoot() {
    testarEficienciaHTTP();
    // ... resto da função
}

Para desativar testes:
void loop() {
    // Comente a linha abaixo para desativar
    // executarTestesEficiencia();
    // ... resto do código
}
*/