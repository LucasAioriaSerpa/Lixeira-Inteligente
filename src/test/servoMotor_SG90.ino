
#include <Arduino.h>
#include <ESP32Servo.h>

const int servoPin = 14;

Servo servo1;

void setup() {
  Serial.begin(9600);
  servo1.attach(servoPin);
  servo1.write(0); //? Set position to 0º
  delay(1000); //? wait for the boy do the movement
  Serial.println("Servo initialized");
}

void loop() {
  for(int posDegrees = 0; posDegrees <= 180; posDegrees++) {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(2);
  }

  for(int posDegrees = 180; posDegrees >= 0; posDegrees--) {
    servo1.write(posDegrees);
    Serial.println(posDegrees);
    delay(2);
  }
}
