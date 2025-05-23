
#include <Arduino.h>

const int maxRange = 30;
const int minRange = 5;

const int TRIG = 13;
const int ECHO = 12;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {

  long duration, inches, cm;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);

  inches = microSecondsToInches(duration);
  cm = microSecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);

}

long microSecondsToInches(long microSeconds) { return microSeconds / 74 / 2; }

long microSecondsToCentimeters(long microSeconds) { return microSeconds / 29 / 2; }
