#include "mq135.h"

volatile long mqValorAnalogico = 0;
volatile bool mqGasDetectado = false;

void initMQ135() {
    pinMode(MQ_PIN_ANALOGICO, INPUT);
    pinMode(MQ_PIN_DIGITAL, INPUT);
}

void atualizarMQ135() {
    long soma = 0;
    for (int i = 0; i < NUM_LEITURAS_MQ; ++i) {
        soma += analogRead(MQ_PIN_ANALOGICO);
        delay(2);
    }
    mqValorAnalogico = soma / NUM_LEITURAS_MQ;
    mqGasDetectado = digitalRead(MQ_PIN_DIGITAL) == HIGH;
}