#include "leds.h"
#include "../sensores/hc_sr04.h"

void initLEDs() {
    pinMode(LED_VERMELHO_INTERNO_PIN, OUTPUT);
    pinMode(LED_AMARELO_INTERNO_PIN, OUTPUT);
    pinMode(LED_VERDE_INTERNO_PIN, OUTPUT);
}

void controlarLEDs() {
    digitalWrite(LED_VERDE_INTERNO_PIN, LOW);
    digitalWrite(LED_AMARELO_INTERNO_PIN, LOW);
    digitalWrite(LED_VERMELHO_INTERNO_PIN, LOW);

    if (distanciaInternaCM >= 30 && distanciaInternaCM <= 40) {
        digitalWrite(LED_VERMELHO_INTERNO_PIN, HIGH);
    } else if (distanciaInternaCM >= 11 && distanciaInternaCM < 30) {
        digitalWrite(LED_AMARELO_INTERNO_PIN, HIGH);
    } else if (distanciaInternaCM <= 10) {
        digitalWrite(LED_VERDE_INTERNO_PIN, HIGH);
    }
}