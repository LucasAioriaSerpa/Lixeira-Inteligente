#include <Arduino.h>
#include <stdio.h>
#include <HX711.h>
#include <WiFi.h>
#include <WebServer.h>

//? Pinos do sensor HC-SR04
#define TRIG_INTERNO_PIN 12
#define ECHO_INTERNO_PIN 13

#define TRIG_EXTERNO_PIN 22
#define ECHO_EXTERNO_PIN 23

//? Pinos dos LEDs
#define LED_VERMELHO_INTERNO_PIN 14
#define LED_AMARELO_INTERNO_PIN 26
#define LED_VERDE_INTERNO_PIN 21

//? Pinos do sensor MQ-135
#define MQ_PIN_ANALOGICO 33
#define MQ_PIN_DIGITAL 25

//? Pinos do sensor de peso HX711
#define HX711_DT_PIN 14
#define HX711_SCK_PIN 12
#define HX711_FATOR_ESCALA 2280.0f

//? Credenciais WiFi
#define WIFI_SSID "Exploda"
#define WIFI_PASSWORD "*******" // TODO: insira sua senha aqui!
// ! IP ESP32 -→ 192.168.15.13

// ? Handles das tarefas
TaskHandle_t HandleParteFisica = NULL;
TaskHandle_t HandleParteConexao = NULL;

// ? Instância do servidor web
WebServer servidor(80);

// ? Variáveis globais para leituras dos sensores
volatile long distanciaInternaCM = 0, mediaDistanciaInternaCM = 0;
const static long maxDistanciaInternaCM = 30, minDistanciaInternaCM = 10;

volatile long distanciaExternaCM = 0, mediaDistanciaExternaCM = 0;
const static  long maxDistanciaExternaCM = 400, minDistanciaExternaCM = 10;

volatile long numPessoasQuePassaram = 0;
volatile long mqValorAnalogico = 0;
volatile bool mqGasDetectado = false;
volatile long hx711Peso = 0;

// ! DEBUG
void debugPrint() {
  Serial.print("Distancia Interna: ");
  Serial.print(distanciaInternaCM);
  Serial.print(" cm, Média: ");
  Serial.print(mediaDistanciaInternaCM);
  Serial.print(" cm, Pessoas Passaram: ");
  Serial.println(numPessoasQuePassaram);

  Serial.print("Distancia Externa: ");
  Serial.print(distanciaExternaCM);
  Serial.print(" cm, Média: ");
  Serial.println(mediaDistanciaExternaCM);

  Serial.print("MQ-135 Valor Analógico: ");
  Serial.println(mqValorAnalogico);
  Serial.print("MQ-135 Gás Detectado: ");
  Serial.println(mqGasDetectado ? "Sim" : "Não");

  Serial.print("HX711 Peso: ");
  Serial.print(hx711Peso);
  Serial.println(" g");
}

// ! PARTE FISICA

// ? Funções do sensor HC-SR04
/**
 * @brief Converte microssegundos para polegadas.
 *
 * Esta função converte o tempo em microssegundos para polegadas com base na velocidade do som.
 *
 * @param microSegundos O tempo em microssegundos.
 * @return A distância em polegadas.
 */
long microssegundosParaPolegadas(long microSegundos) { return microSegundos / 74 / 2; }

/**
 * @brief Converte microssegundos para centímetros.
 *
 * Esta função converte o tempo em microssegundos para centímetros com base na velocidade do som.
 *
 * @param microSegundos O tempo em microssegundos.
 * @return A distância em centímetros.
 */
long microssegundosParaCentimetros(long microSegundos) { return microSegundos / 29 / 2; }

/**
 * @brief Converte microssegundos para porcentagem.
 *
 * Esta função converte o tempo em microssegundos para uma porcentagem baseada em um alcance máximo.
 *
 * @param microSegundos O tempo em microssegundos.
 * @param alcanceMaximo O alcance máximo para a conversão.
 * @return A representação percentual do tempo em microssegundos.
 */
long microssegundosParaPorcentagem(long microSegundos, long alcanceMaximo) {
  if (alcanceMaximo <= 0) return 0; // ? Evita divisão por zero
  return (microSegundos * 100) / alcanceMaximo;
}

/**
 * @brief Mede a distância até um objeto usando um sensor ultrassônico.
 *
 * Esta função aciona o sensor ultrassônico enviando um pulso curto no pino de trigger especificado,
 * depois mede o tempo que o eco leva para retornar no pino de echo especificado. A duração é
 * convertida para centímetros usando a função microssegundosParaCentimetros.
 *
 * @param trigPin O pino digital conectado ao trigger do sensor ultrassônico.
 * @param echoPin O pino digital conectado ao echo do sensor ultrassônico.
 * @return A distância medida em centímetros. Retorna 0 se nenhum eco for recebido em 30ms.
 */
long leituraUnicaCM(int trigPin, int echoPin, int trigDelay, int timeout) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(trigDelay);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(trigDelay);
  digitalWrite(trigPin, LOW);
  long duracao = pulseIn(echoPin, HIGH, timeout); // * timeout de 30ms
  return microssegundosParaCentimetros(duracao);
}

/**
 * @brief Lê a distância média de um sensor ultrassônico em múltiplas amostras.
 *
 * Esta função realiza múltiplas leituras do sensor ultrassônico e calcula a distância média
 * em centímetros. Filtra leituras inválidas que estejam fora de um intervalo especificado.
 *
 * @param trigPin O pino digital conectado ao trigger do sensor ultrassônico.
 * @param echoPin O pino digital conectado ao echo do sensor ultrassônico.
 * @param trigDelay O delay em microssegundos para acionar o sensor.
 * @param numAmostras O número de amostras para calcular a média.
 * @return A distância média em centímetros, ou 0 se nenhuma leitura válida for obtida.
 */
long lerDistanciaMediaCM(int trigPin, int echoPin, int trigDelay, int numAmostras) {
  long soma = 0;
  int leiturasValidas = 0;
  for (int i = 0; i < numAmostras; i++) {
    long d = leituraUnicaCM(trigPin, echoPin, trigDelay, 30000);
    if (d > 0 && d < 400) { // ? Verificação de faixa válida
      soma += d;
      leiturasValidas++;
    }
    vTaskDelay(5); // ? Delay reduzido para resposta mais rápida
  }
  return (leiturasValidas > 0) ? soma / leiturasValidas : 0;
}

/**
 * @brief Conta o número de pessoas que passaram com base na distância medida.
 *
 * Esta função utiliza um histórico de leituras para calcular a média e determinar se uma pessoa
 * passou com base na distância medida pelo sensor ultrassônico. Incrementa o contador de pessoas
 * se a distância atual for significativamente maior que a média.
 *
 * @return O número total de pessoas que passaram.
 */
long contatorPessoas() {
  static const int numAmostras = 10;
  static long historico[numAmostras] = {0};
  static int indice = 0;
  static bool pessoaContada = false;
  historico[indice++] = distanciaExternaCM;
  if (indice >= numAmostras) indice = 0;
  long soma = 0;
  for (int i = 0; i < numAmostras; ++i) soma += historico[i];
  long media = soma / numAmostras;
  if (!pessoaContada && distanciaExternaCM > media + 5) {
    ++numPessoasQuePassaram;
    pessoaContada = true;
  }
  if (pessoaContada && distanciaExternaCM <= media) pessoaContada = false;
  return numPessoasQuePassaram;
}

//? Função para leitura de Amonia
/**
 * @brief Lê o valor do sensor MQ-135 e verifica se o gás amônia foi detectado.
 *
 * Esta função lê o valor analógico do sensor MQ-135 e verifica se o pino digital indica
 * a presença de gás amônia. Imprime os valores no monitor serial.
*/
void lerAmonia() {
  mqValorAnalogico = analogRead(MQ_PIN_ANALOGICO);
  mqGasDetectado = digitalRead(MQ_PIN_DIGITAL) == HIGH; // ? Considera "HIGH" como gás detectado
}

//? Função para leitura de peso com HX711
/**
 * @brief Lê o peso do sensor HX711.
 *
 * Esta função lê o valor do sensor HX711 e converte para gramas ou quilogramas.
 * O valor é impresso no monitor serial.
*/
void lerPesoHX711() {
  HX711 hx711;
  hx711.begin(HX711_DT_PIN, HX711_SCK_PIN);
  hx711Peso = 0;
  for (int i = 0; i < 10; i++) {hx711Peso += hx711.read();}
  hx711Peso /= 10;
  hx711Peso = hx711Peso / HX711_FATOR_ESCALA;
  hx711Peso = hx711Peso < 0 ? 0 : hx711Peso;
}

// ? TASK
/**
 * @brief Função de tarefa que gerencia a parte física do sistema.
 *
 * Esta função deve ser executada como uma tarefa FreeRTOS. Ela executa continuamente
 * em um loop infinito, imprimindo "Tarefa Parte Física rodando!" no monitor serial a cada segundo.
 * O atraso entre as impressões é feito usando vTaskDelay.
 *
 * @param pvParameters Ponteiro para os parâmetros passados para a tarefa (não utilizado).
*/
void ParteFisica(void *pvParameters) {
  for (;;) {
    Serial.println("Tarefa Parte Física rodando!");
    // ? Leitura dos sensores de distância
    distanciaExternaCM = lerDistanciaMediaCM(TRIG_EXTERNO_PIN, ECHO_EXTERNO_PIN, 5, 5);
    mediaDistanciaExternaCM = (mediaDistanciaExternaCM + distanciaExternaCM) / 2;
    vTaskDelay(pdMS_TO_TICKS(10)); // ? Delay para evitar leituras muito rápidas
    distanciaInternaCM = lerDistanciaMediaCM(TRIG_INTERNO_PIN, ECHO_INTERNO_PIN, 10, 5);
    mediaDistanciaInternaCM = (mediaDistanciaInternaCM + distanciaInternaCM) / 2;
    // ? Controle dos LEDs
    digitalWrite(LED_VERDE_INTERNO_PIN, LOW);
    digitalWrite(LED_AMARELO_INTERNO_PIN, LOW);
    digitalWrite(LED_VERMELHO_INTERNO_PIN, LOW);
    if (mediaDistanciaInternaCM >= 30 && mediaDistanciaInternaCM <= 40) {
      Serial.println("Lixeira vazia");
      digitalWrite(LED_VERMELHO_INTERNO_PIN, HIGH);
    } else if (mediaDistanciaInternaCM >= 11 && mediaDistanciaInternaCM < 30) {
      Serial.println("Lixeira meio termo");
      digitalWrite(LED_AMARELO_INTERNO_PIN, HIGH);
    } else if (mediaDistanciaInternaCM <= 10 && mediaDistanciaInternaCM >= 5) {
      Serial.println("Lixeira cheia");
      digitalWrite(LED_VERDE_INTERNO_PIN, HIGH);
    }
    // ? Verificação de pessoas passando
    contatorPessoas();
    // ? Leitura do sensor MQ-135
    lerAmonia();
    // ? Leitura do sensor de peso HX711
    lerPesoHX711();
  }
}

// ! PARTE CONEXÃO

/**
 * @brief Manipula a rota raiz do servidor web.
 *
 * Esta função é chamada quando a rota raiz ("/") é acessada. Ela coleta dados dos sensores,
 * formata esses dados em JSON e os envia como resposta HTTP.
*/
void handleRoot() {
  /* // * json:
  {
    "distanciaInternaCM": xCm,
    "porcentagemInterna": x%,
    "distanciaExternaCM": xCm,
    "QuantidadeDePessoasQuePassaram": x,
    "mqValorAnalogico": x,
    "mqGasDetectado": true/false,
    "hx711Peso": xg/kg
  }
  */
  String json = "{";
  json += "\"distanciaInternaCM\":" + String(mediaDistanciaInternaCM) + ",";
  json += "\"porcentagemInterna\":" + String(microssegundosParaPorcentagem(mediaDistanciaInternaCM, maxDistanciaInternaCM)) + ",";
  json += "\"distanciaExternaCM\":" + String(mediaDistanciaExternaCM) + ",";
  json += "\"QuantidadeDePessoasQuePassaram\":" + String(numPessoasQuePassaram) + ",";
  json += "\"mqValorAnalogico\":" + String(mqValorAnalogico) + ",";
  json += "\"mqGasDetectado\":" + String(mqGasDetectado ? "true" : "false") + ",";
  json += "\"hx711Peso\":" + String(hx711Peso);
  json += "}";
  servidor.sendHeader("Access-Control-Allow-Origin", "*");
  servidor.sendHeader("Access-Control-Allow-Methods", "GET");
  servidor.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  servidor.send(200, "application/json", json);
}

/**
 * @brief Configura a conexão WiFi.
 *
 * Esta função inicia a conexão WiFi com as credenciais fornecidas.
 * Ela imprime o status da conexão no monitor serial e exibe o endereço IP local
 * quando a conexão é bem-sucedida.
*/
void setupWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando-se ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado ao WiFi!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

// ? TASK
/**
 * @brief Função de tarefa que gerencia a parte de conexão do sistema.
 *
 * Esta função deve ser executada como uma tarefa FreeRTOS. Ela configura o servidor web,
 * define as rotas e aguarda requisições do cliente em um loop infinito.
 *
 * @param pvParameters Ponteiro para os parâmetros passados para a tarefa (não utilizado).
*/
void ParteConexao(void *pvParameters) {
  // ? Configuração do servidor web
  servidor.on("/", HTTP_GET, handleRoot);     // ? Rota root
  servidor.begin();                           // ? Inicia o servidor web
  Serial.println("Servidor web iniciado!");
  for (;;) {
    servidor.handleClient();                  // ? Aguarda requisições do client
    vTaskDelay(pdMS_TO_TICKS(10));            // ? Pequeno delay para evitar uso excessivo da CPU :]
  }
}

void setup() {
  Serial.begin(9600);
  // ? Configuração dos pinos
  pinMode(TRIG_INTERNO_PIN, OUTPUT);
  pinMode(ECHO_INTERNO_PIN, INPUT);
  pinMode(TRIG_EXTERNO_PIN, OUTPUT);
  pinMode(ECHO_EXTERNO_PIN, INPUT);
  pinMode(LED_VERMELHO_INTERNO_PIN, OUTPUT);
  digitalWrite(LED_VERMELHO_INTERNO_PIN, HIGH);
  delay(100);
  digitalWrite(LED_VERMELHO_INTERNO_PIN, LOW);
  pinMode(LED_AMARELO_INTERNO_PIN, OUTPUT);
  digitalWrite(LED_AMARELO_INTERNO_PIN, HIGH);
  delay(100);
  digitalWrite(LED_AMARELO_INTERNO_PIN, LOW);
  pinMode(LED_VERDE_INTERNO_PIN, OUTPUT);
  digitalWrite(LED_VERDE_INTERNO_PIN, HIGH);
  delay(100);
  digitalWrite(LED_VERDE_INTERNO_PIN, LOW);
  pinMode(MQ_PIN_ANALOGICO, INPUT);
  pinMode(MQ_PIN_DIGITAL, INPUT);
  pinMode(HX711_DT_PIN, INPUT);
  pinMode(HX711_SCK_PIN, OUTPUT);
  // ? Configuração do Conexão Wifi
  setupWifi();
  // ? xTaskCreate startando as tarefas:
  xTaskCreate(
    ParteFisica,            // ? Função da tarefa
    "ParteFisica",          // ? Nome
    2048,                   // ? Tamanho da pilha (ESP32 precisa de mais, ex: 2048 bytes)
    NULL,                   // ? Parâmetros
    1,                      // ? Prioridade
    &HandleParteFisica      // ? Handle da tarefa
  );
  xTaskCreate(
    ParteConexao,
    "ParteConexao",
    4096,
    NULL,
    1,
    &HandleParteConexao
  );
}

void loop(){}
