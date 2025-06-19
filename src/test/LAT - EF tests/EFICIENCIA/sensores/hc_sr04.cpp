#include "hc_sr04.h"

volatile long distanciaInternaCM = 0;
volatile long distanciaExternaCM = 0;

static long microssegundosParaCentimetros(long microSegundos) {
    return microSegundos / 29 / 2;
}

void initHC_SR04() {
    pinMode(TRIG_INTERNO_PIN, OUTPUT);
    pinMode(ECHO_INTERNO_PIN, INPUT);
    pinMode(TRIG_EXTERNO_PIN, OUTPUT);
    pinMode(ECHO_EXTERNO_PIN, INPUT);
}

long lerDistanciaCM(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    return microssegundosParaCentimetros(pulseIn(echoPin, HIGH, TIMEOUT_LEITURA));
}

long lerDistanciaMediaCM(int trigPin, int echoPin) {
    long soma = 0;
    int leiturasValidas = 0;
    for (int i = 0; i < NUM_AMOSTRAS; i++) {
        long d = lerDistanciaCM(trigPin, echoPin);
        if (d > 0 && d < 400) {
            soma += d;
            leiturasValidas++;
        }
        delay(5);
    }
    return (leiturasValidas > 0) ? soma / leiturasValidas : 0;
}

void atualizarDistancias() {
    distanciaExternaCM = lerDistanciaMediaCM(TRIG_EXTERNO_PIN, ECHO_EXTERNO_PIN);
    distanciaInternaCM = lerDistanciaMediaCM(TRIG_INTERNO_P