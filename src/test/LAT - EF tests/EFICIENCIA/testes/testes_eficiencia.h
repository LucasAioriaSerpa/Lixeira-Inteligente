#ifndef TESTES_EFICIENCIA_H
#define TESTES_EFICIENCIA_H

#include <Arduino.h>

/**
 * @file testes_eficiencia.h
 * @brief Módulo de testes de desempenho do sistema
 * 
 * Este módulo fornece funções para medir a eficiência de operação
 * de todos os componentes principais do sistema.
 */

/**
 * @brief Executa todos os testes de eficiência disponíveis
 * 
 * Esta função coordena a execução de todos os testes individuais
 * e deve ser chamada no loop principal.
 */
void executarTestesEficiencia();

/**
 * @brief Testa a eficiência do sensor HC-SR04 interno
 * 
 * Mede quantas leituras por segundo o sensor ultrassônico interno
 * consegue realizar, considerando o cálculo de média.
 */
void testarEficienciaHCSR04Interno();

/**
 * @brief Testa a eficiência do sensor HC-SR04 externo
 * 
 * Mede quantas leituras por segundo o sensor ultrassônico externo
 * consegue realizar, considerando o cálculo de média.
 */
void testarEficienciaHCSR04Externo();

/**
 * @brief Testa a eficiência do sensor MQ-135
 * 
 * Mede quantas leituras analógicas/digitais por segundo
 * o sensor de gás consegue realizar.
 */
void testarEficienciaMQ135();

/**
 * @brief Testa a eficiência do sensor HX711
 * 
 * Mede quantas leituras de peso por segundo
 * a célula de carga consegue realizar.
 */
void testarEficienciaHX711();

/**
 * @brief Testa a eficiência do sistema de LEDs
 * 
 * Mede quantas operações de mudança de estado
 * os LEDs conseguem realizar por segundo.
 */
void testarEficienciaLEDs();

/**
 * @brief Testa a eficiência do servidor HTTP
 * 
 * Mede quantas requisições por segundo o servidor web
 * consegue processar. Deve ser chamada dentro de handleRoot().
 */
void testarEficienciaHTTP();

#endif // TESTES_EFICIENCIA_H


/**
Como integrar com o restante do sistema:

No arquivo principal:
#include "testes/testes_eficiencia.h"

void loop() {
    executarTestesEficiencia(); // Para testes contínuos
    // ...
}

No servidor web:
#include "testes/testes_eficiencia.h"

void handleRoot() {
    testarEficienciaHTTP(); // Medir desempenho do servidor
    // ...
}

Para testes individuais:
// Em qualquer módulo que precise testar um componente específico
#include "testes/testes_eficiencia.h"

void minhaFuncao() {
    testarEficienciaHX711(); // Teste pontual
    // ...
}

*/