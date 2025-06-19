#ifndef MQ135_H
#define MQ135_H

#include <Arduino.h>

#define MQ_PIN_ANALOGICO 34
#define MQ_PIN_DIGITAL 25
#define NUM_LEITURAS_MQ 5

void initMQ135();
void atualizarMQ135();

extern volatile long mqValorAnalogico;
extern volatile bool mqGasDetectado;

#endif