#include <Arduino.h>

const int GREEN_LED = 14;
const int YELLOW_LED = 26;
const int RED_LED = 21;

struct Led {
  int pin;
  const char* color;
};

Led leds[] = {
  {GREEN_LED, "Green"},
  {YELLOW_LED, "Yellow"},
  {RED_LED, "Red"}
};

void setup() {
  Serial.begin(9600);
  for (auto& led : leds) {
    pinMode(led.pin, OUTPUT);
  }
}

void onOffLed(const Led& led) {
  Serial.print("LED -> ");
  Serial.println(led.color);
  digitalWrite(led.pin, HIGH);
  delay(50);
  digitalWrite(led.pin, LOW);
}

void loop() {
  for (auto& led : leds) {
    onOffLed(led);
    delay(10);
  }
}
