// ! NÃO UTILIZAR PINO 35 E 34

#include <Arduino.h>

constexpr int maxRange = 30;
constexpr int minRange = 5;
constexpr int trigDelay = 10;
constexpr int numSamples = 5;

const int TRIG_1 = 33;
const int ECHO_1 = 32;
const int RED_1 = 12;
const int YELLOW_1 = 14;
const int GREEN_1 = 27;

const int TRIG_2 = 25;
const int ECHO_2 = 13;
const int RED_2 = 26;
const int GREEN_2 = 35;

long microSecondsToCentimeters(long microSeconds)
{
    return microSeconds / 29 / 2;
}

long singleReadCM(int trigPin, int echoPin)
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(trigDelay);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH, 30000); // ? timeout de 30ms
    return microSecondsToCentimeters(duration);
}

long readDistanceAvgCM(int trigPin, int echoPin)
{
    long sum = 0;
    int validReads = 0;
    for (int i = 0; i < numSamples; i++)
    {
        long d = singleReadCM(trigPin, echoPin);
        if (d > 0 && d < 400)
        {
            sum += d;
            validReads++;
        }
        delay(2);
    }
    return (validReads > 0) ? sum / validReads : 0;
}

void setup()
{
    Serial.begin(9600);
    pinMode(TRIG_1, OUTPUT);
    pinMode(ECHO_1, INPUT);
    pinMode(RED_1, OUTPUT);
    pinMode(YELLOW_1, OUTPUT);
    pinMode(GREEN_1, OUTPUT);

    pinMode(TRIG_2, OUTPUT);
    pinMode(ECHO_2, INPUT);
    pinMode(RED_2, OUTPUT);
    pinMode(GREEN_2, OUTPUT);
}

void loop()
{
    long cm1 = readDistanceAvgCM(TRIG_1, ECHO_1);
    delay(10); // ? evitar interferência entre os sensores
    long cm2 = readDistanceAvgCM(TRIG_2, ECHO_2);

    Serial.println("Sensor 1: " + String(cm1) + " cm | Sensor 2: " + String(cm2) + " cm");

    // ? LED lógicos do Sensor 1
    if (cm1 >= maxRange)
    {
        digitalWrite(RED_1, LOW);
        digitalWrite(YELLOW_1, LOW);
        digitalWrite(GREEN_1, HIGH);
    }
    else if (cm1 >= minRange)
    {
        digitalWrite(RED_1, LOW);
        digitalWrite(GREEN_1, LOW);
        digitalWrite(YELLOW_1, HIGH);
    }
    else
    {
        digitalWrite(YELLOW_1, LOW);
        digitalWrite(GREEN_1, LOW);
        digitalWrite(RED_1, HIGH);
    }
    // ? LED lógicos do Sensor 2
    if (cm2 < maxRange && cm2 > 0)
    {
        digitalWrite(RED_2, LOW);
        digitalWrite(GREEN_2, HIGH);
    }
    else
    {
        digitalWrite(GREEN_2, LOW);
        digitalWrite(RED_2, HIGH);
    }

    delay(5);
}
