#include <Arduino.h>
#include <stdio.h>

#define RED_PIN 12
#define YELLOW_PIN 14
#define GREEN_PIN 27

// Task handles (optional)
TaskHandle_t Task1Handle = NULL;
TaskHandle_t Task2Handle = NULL;

// Example task functions
void Task1(void *pvParameters) {
  for (;;) {
    Serial.println("Task 1 running");
    digitalWrite(YELLOW_PIN, HIGH);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    digitalWrite(YELLOW_PIN, LOW);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void Task2(void *pvParameters) {
  for (;;) {
    Serial.println("Task 2 running");
    digitalWrite(RED_PIN, HIGH);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    digitalWrite(RED_PIN, LOW);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(9600);
  // config LEDS
  Serial.println("LED-TESTING");
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  digitalWrite(RED_PIN, HIGH);
  delay(100);
  digitalWrite(RED_PIN, LOW);
  delay(100);
  digitalWrite(YELLOW_PIN, HIGH);
  delay(100);
  digitalWrite(YELLOW_PIN, LOW);
  delay(100);
  digitalWrite(GREEN_PIN, HIGH);
  delay(100);
  digitalWrite(GREEN_PIN, LOW);
  delay(100);

  // Create tasks
  xTaskCreate(
    Task1,           // Task function
    "Task1",         // Name
    2048,            // Stack size (ESP32 needs more stack, e.g., 2048 bytes)
    NULL,            // Parameters
    1,               // Priority
    &Task1Handle     // Task handle
  );

  xTaskCreate(
    Task2,
    "Task2",
    2048,           // Stack size for ESP32
    NULL,
    1,
    &Task2Handle
  );
}

void loop()
{
  // Empty. Tasks run independently.
}
