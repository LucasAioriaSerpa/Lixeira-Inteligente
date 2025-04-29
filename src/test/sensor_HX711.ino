
#include "HX711.h"

const int LOADCELL_DT_PIN = 16;
const int LOADCELL_SCK_PIN = 4;

HX711 scale;

void setup() {
  Serial.begin(115200);
  scale.begin(LOADCELL_DT_PIN, LOADCELL_SCK_PIN); // ? Inicializa a escala
}

void loop() {
  if (scale.is_ready()) {
    long reading = scale.get_units();
    Serial.print("peso dentro da lixeira: ");
    Serial.print(reading, 1);
    Serial.println("g");
  } else {
    Serial.println("HX711 not found!");
  }
  delay(1000);
}
