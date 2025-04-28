
#include <Arduino.h>

#define PIN_TRIG 0
#define PIN_ECHO 2

double altura = 44; // ? altura maxima

void setup()
{
    Serial.begin(115200);
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

void loop()
{
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);

    /*
    ! Levando em consideração que a lixeira !
    ! tem 37cm de largura e 44cm de altura !
    */

    // * pega o valor do Pulso e transforma em CM
    double duration = (pulseIn(PIN_ECHO, HIGH) / 58);
    double porcentagemDoRecheio = (1 - (duration / altura)) * 100;
    Serial.print("Porcentagem do recheio: ");
    Serial.print(porcentagemDoRecheio);
    Serial.println("%");

    delay(1000);
}
