#include <Arduino.h>

// Pinos 
#define YELLOW_PIN 14
#define GREEN_PIN 27

// Filas e Handles
QueueHandle_t xQueue;
TaskHandle_t Task1Handle = NULL;
TaskHandle_t Task2Handle = NULL;

// Variáveis de tempo
unsigned long task1CreateTime = 0;
volatile unsigned long eventTriggerTime = 0;

void setup() {
  Serial.begin(9600);

  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  // Cria fila para comunicação entre tarefas
  xQueue = xQueueCreate(10, sizeof(unsigned long));

  // Marca o tempo antes da criação da Task1
  task1CreateTime = millis();

  // Cria Task1 e Task2
  xTaskCreate(Task1, "Task1", 2048, NULL, 1, &Task1Handle);
  xTaskCreate(Task2, "Task2", 2048, NULL, 1, &Task2Handle);
}

void loop() {
  // Disparar evento para Task1
  eventTriggerTime = millis();
  xTaskNotifyGive(Task1Handle);
  delay(2000);
}

// -------------------- TASK 1 --------------------
void Task1(void *pvParameters) {
  // Medir tempo de inicialização da Task1
  unsigned long task1StartTime = millis();
  Serial.print("[Task1] Tempo de inicialização: ");
  Serial.print(task1StartTime - task1CreateTime);
  Serial.print(" ms");
  Serial.println("");

  for (;;) {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // Tempo de resposta
    unsigned long responseTime = millis() - eventTriggerTime;
    Serial.print("[Task1] Tempo de resposta: ");
    Serial.print(responseTime);
    Serial.print(" ms");
    Serial.println("");

    // Comunicação com Task2 
    unsigned long sendTime = micros(); 
    xQueueSend(xQueue, &sendTime, portMAX_DELAY);

    // Processamento de dados 
    unsigned long startProc = micros();
    digitalWrite(YELLOW_PIN, HIGH);
    delay(100); 
    digitalWrite(YELLOW_PIN, LOW);
    unsigned long endProc = micros();

    float processingTimeMs = (endProc - startProc) / 1000.0; // conversão para ms
    Serial.print("[Task1] Tempo de processamento: ");
    Serial.print(processingTimeMs, 2); // 2 casas decimais
    Serial.print(" ms");
    Serial.println("");

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// -------------------- TASK 2 --------------------
void Task2(void *pvParameters) {
  for (;;) {
    unsigned long receivedTime = 0;

    if (xQueueReceive(xQueue, &receivedTime, portMAX_DELAY)) {
      unsigned long now = micros();
      float commTimeMs = (now - receivedTime) / 1000.0; // conversão para ms

      Serial.print("[Task2] Tempo de comunicação entre tarefas: ");
      Serial.print(commTimeMs, 3);
      Serial.print(" ms");
      Serial.println("");

      // Indicador visual
      digitalWrite(GREEN_PIN, HIGH);
      delay(50);
      digitalWrite(GREEN_PIN, LOW);
    }
  }
}
