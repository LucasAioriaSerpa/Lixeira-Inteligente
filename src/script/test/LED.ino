
#include <string>

#define GREEN_LED 0
#define YELLOW_LED 4
#define RED_LED 16

void setup()
{
  Serial.begin(115200);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
}

void onOffLed(int LED, String color)
{
  Serial.print("LED -> ");
  Serial.println(color);
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
}

void loop()
{
  onOffLed(GREEN_LED, "Green");
  delay(1000);
  onOffLed(YELLOW_LED, "Yellow");
  delay(1000);
  onOffLed(RED_LED, "Red");
  delay(1000);
}
