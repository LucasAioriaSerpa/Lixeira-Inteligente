#ifndef HX711_H
#define HX711_H

#include <Arduino.h>
#include <HX711.h>

#define HX711_DT_PIN 18
#define HX711_SCK_PIN 19
#define HX711_FATOR_ESCALA 2280.0f

void initHX711();
void atualizarPeso();

extern volatile long hx711Peso;

#endif