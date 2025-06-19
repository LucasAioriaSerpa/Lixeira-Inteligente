#include <Arduino.h>

const int TRIG = 22;
const int ECHO = 23;

unsigned long tempoInicializacao = 0;
bool inicializou = false;


// Converte duração do pulso em cm
long microsegundosParaCM(long microsegundos) {
  return microsegundos / 29 / 2;
}

// Converte microssegundos em milissegundos
float usParaMs(unsigned long us) {
  return us / 1000.0;
}


float medirDistanciaCM(unsigned long &tempoResposta, unsigned long &tempoProcessamento) {
  unsigned long t0 = micros();

  // Envia pulso no TRIG
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Mede o tempo de resposta do sensor
  unsigned long tempoPulso = pulseIn(ECHO, HIGH, 30000); 

  unsigned long t1 = micros();
  tempoResposta = t1 - t0;

  // Tempo de processamento dos dados 
  unsigned long t2 = micros();
  long distancia = microsegundosParaCM(tempoPulso);
  unsigned long t3 = micros();
  tempoProcessamento = t3 - t2;

  return distancia;
}

// SIMULAÇÃO DE COMUNICAÇÃO ENTRE MÓDULOS 
void simularComunicacaoSensorParaOutroModulo(unsigned long &tempoComunicacao, float valor) {
  unsigned long t0 = micros();

  float recebido = valor; // outro módulo "recebe"
  (void)recebido; // evita warning

  unsigned long t1 = micros();
  tempoComunicacao = t1 - t0;
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Marca tempo de inicialização
  tempoInicializacao = millis();
}


void loop() {
  if (!inicializou) {
    // Aguarda o sensor estabilizar
    delay(100);
    Serial.print("Tempo de Inicialização do Módulo: ");
    Serial.print(millis() - tempoInicializacao);
    Serial.print(" ms");
    Serial.println("");
    inicializou = true;
  }

  unsigned long tempoResposta = 0;
  unsigned long tempoProcessamento = 0;
  unsigned long tempoComunicacao = 0;

  float distancia = medirDistanciaCM(tempoResposta, tempoProcessamento);
  simularComunicacaoSensorParaOutroModulo(tempoComunicacao, distancia);

  Serial.print("Tempo de Resposta da Leitura: ");
  Serial.print(usParaMs(tempoResposta));
  Serial.print(" ms");
  Serial.println("");

  Serial.print("Tempo de Processamento dos Dados: ");
  Serial.print(usParaMs(tempoProcessamento));
  Serial.print(" ms");
  Serial.println("");

  Serial.print("Tempo de Comunicação com outro módulo: ");
  Serial.print(usParaMs(tempoComunicacao));
  Serial.print(" ms");
  Serial.println("");

  Serial.print("Distância medida: ");
  Serial.print(distancia);
  Serial.print(" cm");
  Serial.println("");

  delay(10000); // intervalo entre leituras
}
