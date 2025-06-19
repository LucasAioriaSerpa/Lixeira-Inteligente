#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>

#define LED_VERMELHO_INTERNO_PIN 14
#define LED_AMARELO_INTERNO_PIN 26
#define LED_VERDE_INTERNO_PIN 21

void initLEDs();
void controlarLEDs();

#endif