#include <Arduino.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define RED_PIN 12
#define YELLOW_PIN 14
#define GREEN_PIN 27

#define RX_PIN 35 //680 owns
#define TX_PIN 34
#define VOLUME_MP3 30

SoftwareSerial playerMP3Serial(RX_PIN, TX_PIN);
DFRobotDFPlayerMini playerMP3;

void setup() {
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
  // config playerMP3
  playerMP3Serial.begin(9600);
  Serial.println(F("Inicializando DFPlayer ... (Esperar entre 3 á 5 segundos)"));
  digitalWrite(YELLOW_PIN, HIGH);
  if (!playerMP3.begin(playerMP3Serial)) {
    digitalWrite(RED_PIN, HIGH);
    Serial.println(F("Falha: "));
    Serial.println(F("1.Conexões!"));
    Serial.println(F("2.Cheque o cartão SD!"));
    digitalWrite(YELLOW_PIN, LOW);
    while (true);
  }
  #ifdef DEBUG
  Serial.println(F("DFPlayer iniciado!"));
  playerMP3.volume(VOLUME_MP3);
  Serial.println("O setup acabou! :3");
  #endif
}

void loop() {
  digitalWrite(GREEN_PIN, HIGH);
  playerMP3.playFolder(1, 1);
  Serial.println("Tocando pasta 01, musica 001");
  delay(5000);
  digitalWrite(GREEN_PIN, LOW);
}
