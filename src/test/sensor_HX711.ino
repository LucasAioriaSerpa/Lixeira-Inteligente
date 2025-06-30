#include <Arduino.h>
#include "HX711.h"

constexpr int DT_PIN = 19;
constexpr int SCK_PIN = 18;
constexpr float SCALE_FACTOR = 2280.0f;

HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println(F("HX711 scale test\nInitializing the scale..."));
  scale.begin(DT_PIN, SCK_PIN);
  delay(1000);
  scale.set_scale(SCALE_FACTOR);
  scale.tare();
  Serial.println(F("Scale initialized"));
}

void loop() {
  long raw = scale.read_average(1);
  float weight = scale.get_units(1);
  Serial.printf("Raw: %ld | Weight: %.1f\n", raw, weight);
  delay(1000);
}
