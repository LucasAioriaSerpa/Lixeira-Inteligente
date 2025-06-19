#include <Arduino.h>
#include "sensores/hc_sr04.h"
#include "sensores/mq135.h"
#include "sensores/hx711.h"
#include "atuadores/leds.h"
#include "conexao/wifi.h"
#include "conexao/server.h"
#include "testes/testes_eficiencia.h"

// Variáveis globais (se necessário)
volatile long numPessoasQuePassaram = 0;

void setup() {
    Serial.begin(9600);
    
    // Inicializa todos os módulos
    initHC_SR04();
    initMQ135();
    initHX711();
    initLEDs();
    initWiFi();
    initServer();
    
    Serial.println("Sistema inicializado");
}

void loop() {
    // Atualiza sensores
    atualizarDistancias();
    atualizarMQ135();
    atualizarPeso();
    
    // Controle de LEDs baseado nos sensores
    controlarLEDs();
    
    // Testes de eficiência (opcional)
    executarTestesEficiencia();
    
    delay(10);
}