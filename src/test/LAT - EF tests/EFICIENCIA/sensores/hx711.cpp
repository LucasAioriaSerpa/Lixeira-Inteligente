#include "hx711.h"

HX711 hx711;
volatile long hx711Peso = 0;

void initHX711() {
    hx711.begin(HX711_DT_PIN, HX711_SCK_PIN);
}

void atualizarPeso() {
    long soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += hx711.read();
    }
    float pesoMedio = static_cast<float>(soma) / 10.0f;
    hx711Peso = static_cast<long>(pesoMedio / HX711_FATOR_ESCALA);
    hx711Peso = hx711Peso < 0 ? 0 : hx711Peso;
}