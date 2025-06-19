#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mp3Serial(16, 17); // RX, TX
DFRobotDFPlayerMini mp3;

unsigned long startTime, endTime;

void setup() {
  Serial.begin(9600);
  mp3Serial.begin(9600);

  // Tempo de inicialização do módulo MP3
  startTime = millis();
  if (!mp3.begin(mp3Serial)) {
    Serial.println("Erro ao iniciar DFPlayer.");
    while (true);
  }
  endTime = millis();

  Serial.print("Tempo de inicialização do módulo: ");
  Serial.print(endTime - startTime);
  Serial.print(" ms");
  Serial.println("");

  mp3.volume(20); // Ajusta volume para evitar picos
}

void loop() {
  // Simulando comando de outra tarefa
  startTime = millis();
  executarComandoMP3(1); // Toca a faixa 1
  endTime = millis();

  Serial.print("Tempo de comunicação entre módulos: ");
  Serial.print(endTime - startTime);
  Serial.print(" ms");
  Serial.println("");

  delay(5000); // Espera entre ciclos
}

void executarComandoMP3(int faixa) {
  // Tempo de processamento de dados recebidos
  unsigned long startProcess = millis();

  // Simula "processamento" interno do comando
  int comando = faixa;
  delay(1); // Processamento leve
  unsigned long endProcess = millis();

  Serial.print("Tempo de processamento de dados: ");
  Serial.print(endProcess - startProcess);
  Serial.print(" ms");
  Serial.println("");

  // Tempo de resposta para execução da tarefa (reprodução)
  unsigned long startPlay = millis();
  mp3.play(comando); // Comando para tocar faixa
  delay(200); // Aguarda buffer/tempo mínimo antes do som
  unsigned long endPlay = millis();

  Serial.print("Tempo de resposta para execução de tarefa: ");
  Serial.print(endPlay - startPlay);
  Serial.print(" ms");
  Serial.println("");
  
}
