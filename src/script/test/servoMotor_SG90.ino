
#include <ESP32Servo.h>

const int SERVO_PIN = 19;

Servo servo;

void setup()
{
  Serial.begin(115200);
  servo.attach(SERVO_PIN, 500, 2400);
}

int pos = 0;

void updateServoPos(int pos)
{
  servo.write(pos);
  Serial.print("position servo: ");
  Serial.println(pos);
  delay(20);
}

void loop()
{
  for (pos = 0; pos <= 180; pos += 1)
  {
    updateServoPos(pos);
  }
  for (pos = 180; pos >= 0; pos -= 1)
  {
    updateServoPos(pos);
  }
}
