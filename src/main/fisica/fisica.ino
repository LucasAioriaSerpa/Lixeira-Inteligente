#include <Arduino.h>

void setupfisica() {
    pinMode(2, output);
}

void loopfisica() {
    digitalWrite(2, high);
    delay(500)
    digitalwrite(2, low);
    delay(500);
}