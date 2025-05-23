
#include <Arduino.h>
#include "HX711.h"

const int DT_PIN = 14;
const int SCK_PIN = 12;

HX711 scale;
void setup() {
  scale.begin(DT_PIN,SCK_PIN);
  delay(1000);
  Serial.begin(9600);
  Serial.println("HX711 scale test");
  Serial.println("Initializing the scale...");
  scale.set_scale(2280.f);
  scale.tare();
  Serial.println("Scale initialized");
}

void loop() {
  Serial.print("Reading: ");
  Serial.println(scale.read_average(1));
  Serial.print("Weight: ");
  Serial.println(scale.get_units(1), 1);
  Serial.print("Tare: ");
  Serial.println(scale.get_units(1, true), 1);
  delay(1000);
}
