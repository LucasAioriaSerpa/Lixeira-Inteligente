#include <Arduino.h>
#include <ESP32Servo.h>

// Pino do Servo Motor
const int servoPin = 14;
Servo servo1;

// Variáveis para medição de tempo
unsigned long startTime;
unsigned long endTime;

void setup() {
  Serial.begin(9600);

  // Tempo de inicialização do módulo
  startTime = millis();
  servo1.attach(servoPin);
  servo1.write(0);
  delay(1000); // Tempo para o servo ir à posição inicial
  endTime = millis();

  Serial.print("Tempo de inicialização do módulo (ms): ");
  Serial.println(endTime - startTime); 

  Serial.println("Servo inicializado");
}

void loop() {
  // Simulando comando externo recebido 
  startTime = millis();
  executarMovimentoServo(90); // Comando para mover o servo
  endTime = millis();

  Serial.print("Tempo de comunicação entre módulos (ms): ");
  Serial.println(endTime - startTime); 

  delay(2000); // Espera entre ciclos
}

void executarMovimentoServo(int posFinal) {
  // Tempo de processamento de dados recebidos
  unsigned long startProcess = millis();

  // Processamento do comando (simples)
  int comando = posFinal;
  delay(1); // Simulando algum processamento
  unsigned long endProcess = millis();

  Serial.print("Tempo de processamento de dados (ms): ");
  Serial.println(endProcess - startProcess);

  // Tempo de resposta do servo
  unsigned long startMove = millis();
  servo1.write(comando);
  delay(500); // Espera tempo suficiente para o servo terminar o movimento
  unsigned long endMove = millis();

  Serial.print("Tempo de resposta para execução de tarefa (ms): ");
  Serial.println(endMove - startMove);
}
