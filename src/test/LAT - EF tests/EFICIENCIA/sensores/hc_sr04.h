#ifndef HC_SR04_H
#define HC_SR04_H

#include <Arduino.h>

// Configuração dos pinos
#define TRIG_INTERNO_PIN 12
#define ECHO_INTERNO_PIN 13
#define TRIG_EXTERNO_PIN 22
#define ECHO_EXTERNO_PIN 23

// Parâmetros
#define TIMEOUT_LEITURA 30000  // 30ms
#define NUM_AMOSTRAS 5

// Interface pública
void initHC_SR04();
long lerDistanciaCM(int trigPin, int echoPin);
long lerDistanciaMediaCM(int trigPin, int echoPin);
void atualizarDistancias();

// Variáveis compartilhadas
extern volatile long distanciaInternaCM;
extern volatile long distanciaExternaCM;

#endif