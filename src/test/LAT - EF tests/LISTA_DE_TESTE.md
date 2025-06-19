# Plano de Testes dos Módulos do ESP32

---

## 1. Módulos do Próprio ESP32

### 1.1 - Conexão WiFi

- **Eficiência**
  - **Uso de memória (RAM/Flash):**  
    Medir o consumo de memória antes e após a inicialização do WiFi utilizando `ESP.getFreeHeap()` e `ESP.getFreeSketchSpace()`.  
    - **Valor medido:** [....................................................]
  - **Estabilidade do funcionamento:**  
    Monitorar o número de desconexões e reinicializações durante um período de operação contínua (ex: 24h), registrando eventos no log serial.  
    - **Valor medido:** [....................................................]
  - **Taxa de sucesso nas operações:**  
    Calcular a porcentagem de tentativas de conexão bem-sucedidas em relação ao total de tentativas realizadas.  
    - **Valor medido:** [....................................................]

- **Latência**
  - **Tempo de resposta para execução de tarefas:**  
    Medir o tempo entre o envio de uma solicitação HTTP ao ESP32 e o recebimento da resposta.  
    - **Valor medido:** [....................................................]
  - **Tempo de inicialização do módulo:**  
    Medir o tempo desde o início do `WiFi.begin()` até o status `WL_CONNECTED`.  
    - **Valor medido:** [....................................................]
  - **Tempo de comunicação entre módulos:**  
    Avaliar o tempo de envio e recebimento de dados entre o ESP32 e outros dispositivos na rede.  
    - **Valor medido:** [....................................................]
  - **Tempo de processamento de dados recebidos:**  
    Medir o tempo entre o recebimento de uma requisição e o envio da resposta pelo servidor web.  
    - **Valor medido:** [....................................................]

---

### 1.2 - xTask (Gerenciamento de Tarefas no ESP32)

- **Eficiência**
  - **Uso de memória (RAM/Flash):**  
    Avaliar o consumo de memória por tarefa utilizando funções do FreeRTOS, como `uxTaskGetStackHighWaterMark()`.  
    - **Valor medido:** [....................................................]
  - **Estabilidade do funcionamento:**  
    Monitorar se as tarefas permanecem ativas e sem falhas durante longos períodos.  
    - **Valor medido:** [....................................................]
  - **Taxa de sucesso nas operações:**  
    Verificar se as tarefas executam suas funções conforme esperado, sem bloqueios ou travamentos.  
    - **Valor medido:** [....................................................]

- **Latência**
  - **Tempo de resposta para execução de tarefas:**  
    Medir o tempo entre o disparo de um evento e a execução da tarefa correspondente.  
    - **Valor medido:** [....................................................]
  - **Tempo de inicialização do módulo:**  
    Medir o tempo desde a chamada de `xTaskCreate()` até o início da execução da tarefa.  
    - **Valor medido:** [....................................................]
  - **Tempo de comunicação entre módulos:**  
    Avaliar o tempo de troca de mensagens entre tarefas (ex: via queues).  
    - **Valor medido:** [....................................................]
  - **Tempo de processamento de dados recebidos:**  
    Medir o tempo de processamento de dados dentro de cada tarefa.  
    - **Valor medido:** [....................................................]

---

## 2. Módulos dos Sensores

### 2.1 - HC-SR04 (x2)

- **Eficiência**
  - **Uso de memória (RAM/Flash):**  
    Verificar o impacto das leituras dos sensores no consumo de memória.  
    - **Valor medido:** [....................................................]
  - **Estabilidade do funcionamento:**  
    Registrar falhas de leitura ou valores fora do esperado.  
    - **Valor medido:** [....................................................]
  - **Taxa de sucesso nas operações:**  
    Calcular a porcentagem de leituras válidas em relação ao total de tentativas.  
    - **Valor medido:** [....................................................]

- **Latência**
  - **Tempo de resposta para execução de tarefas:**  
    Medir o tempo entre o comando de leitura e a obtenção do valor.  
    - **Valor medido:** [....................................................]
  - **Tempo de inicialização do módulo:**  
    Medir o tempo necessário para o sensor estar pronto após o boot.  
    - **Valor medido:** [....................................................]
  - **Tempo de comunicação entre módulos:**  
    Avaliar o tempo de envio dos dados do sensor para outras tarefas ou módulos.  
    - **Valor medido:** [....................................................]
  - **Tempo de processamento de dados recebidos:**  
    Medir o tempo de processamento dos dados de distância.  
    - **Valor medido:** [....................................................]

---

### 2.2 -.  -LEDs (Vermelho, Amarelo, Verde)

- **Eficiência**
  - **Uso de memória (RAM/Flash):**  
    Avaliar o consumo de memória relacionado ao controle dos LEDs.  
    - **Valor medido:** [....................................................]
  - **Estabilidade do funcionamento:**  
    Monitorar se os LEDs respondem corretamente aos comandos durante longos períodos.  
    - **Valor medido:** [....................................................]
  - **Taxa de sucesso nas operações:**  
    Verificar a porcentagem de comandos de acendimento/apagamento executados corretamente.  
    - **Valor medido:** [....................................................]

- **Latência**
  - **Tempo de resposta para execução de tarefas:**  
    Medir o tempo entre o comando de acender/apagar e a resposta visual do LED.  
    - **Valor medido:** [....................................................]
  - **Tempo de inicialização do módulo:**  
    Medir o tempo para os LEDs estarem prontos após o boot.  
    - **Valor medido:** [....................................................]
  - **Tempo de comunicação entre módulos:**  
    Avaliar o tempo de resposta a comandos vindos de outras tarefas.  
    - **Valor medido:** [....................................................]
  - **Tempo de processamento de dados recebidos:**  
    Medir o tempo de processamento dos comandos de controle dos LEDs.  
    - **Valor medido:** [....................................................]

---

### 2.3 - MQ-135

- **Eficiência**
  - **Uso de memória (RAM/Flash):**  
    Medir o consumo de memória durante leituras do sensor.  
    - **Valor medido:** [....................................................]
  - **Estabilidade do funcionamento:**  
    Monitorar leituras anômalas ou falhas de detecção.  
    - **Valor medido:** [....................................................]
  - **Taxa de sucesso nas operações:**  
    Calcular a porcentagem de leituras válidas.  
    - **Valor medido:** [....................................................]

- **Latência**
  - **Tempo de resposta para execução de tarefas:**  
    Medir o tempo entre o comando de leitura e a obtenção do valor.  
    - **Valor medido:** [....................................................]
  - **Tempo de inicialização do módulo:**  
    Medir o tempo necessário para o sensor estar pronto após o boot.  
    - **Valor medido:** [....................................................]
  - **Tempo de comunicação entre módulos:**  
    Avaliar o tempo de envio dos dados do sensor para outras tarefas.  
    - **Valor medido:** [....................................................]
  - **Tempo de processamento de dados recebidos:**  
    Medir o tempo de processamento dos dados do sensor.  
    - **Valor medido:** [....................................................]

---

### 2.4 - HX711 + Célula de Carga

- **Eficiência**
  - **Uso de memória (RAM/Flash):**  
    Avaliar o consumo de memória durante leituras do sensor.  
    - **Valor medido:** [....................................................]
  - **Estabilidade do funcionamento:**  
    Monitorar falhas de leitura ou valores inconsistentes.  
    - **Valor medido:** [....................................................]
  - **Taxa de sucesso nas operações:**  
    Calcular a porcentagem de leituras válidas.  
    - **Valor medido:** [....................................................]

- **Latência**
  - **Tempo de resposta para execução de tarefas:**  
    Medir o tempo entre o comando de leitura e a obtenção do valor.  
    - **Valor medido:** [....................................................]
  - **Tempo de inicialização do módulo:**  
    Medir o tempo necessário para o sensor estar pronto após o boot.  
    - **Valor medido:** [....................................................]
  - **Tempo de comunicação entre módulos:**  
    Avaliar o tempo de envio dos dados do sensor para outras tarefas.  
    - **Valor medido:** [....................................................]
  - **Tempo de processamento de dados recebidos:**  
    Medir o tempo de processamento dos dados do sensor.  
    - **Valor medido:** [....................................................]

---

## 3. Módulo Servo Motor SG90

- **Eficiência**
  - **Uso de memória (RAM/Flash):**  
    Medir o consumo de memória ao acionar o servo.  
    - **Valor medido:** [....................................................]
  - **Estabilidade do funcionamento:**  
    Monitorar travamentos ou falhas de movimento.  
    - **Valor medido:** [....................................................]
  - **Taxa de sucesso nas operações:**  
    Calcular a porcentagem de movimentos executados corretamente.  
    - **Valor medido:** [....................................................]

- **Latência**
  - **Tempo de resposta para execução de tarefas:**  
    Medir o tempo entre o comando de movimento e a resposta do servo.  
    - **Valor medido:** [....................................................]
  - **Tempo de inicialização do módulo:**  
    Medir o tempo para o servo estar pronto após o boot.  
    - **Valor medido:** [....................................................]
  - **Tempo de comunicação entre módulos:**  
    Avaliar o tempo de resposta a comandos vindos de outras tarefas.  
    - **Valor medido:** [....................................................]
  - **Tempo de processamento de dados recebidos:**  
    Medir o tempo de processamento dos comandos de controle do servo.  
    - **Valor medido:** [....................................................]

---

## 4. Módulo DFPlayer-MP3

- **Eficiência**
  - **Uso de memória (RAM/Flash):**  
    Medir o consumo de memória ao acionar o módulo.  
    - **Valor medido:** [....................................................]
  - **Estabilidade do funcionamento:**  
    Monitorar falhas de reprodução ou travamentos.  
    - **Valor medido:** [....................................................]
  - **Taxa de sucesso nas operações:**  
    Calcular a porcentagem de execuções de áudio bem-sucedidas.  
    - **Valor medido:** [....................................................]

- **Latência**
  - **Tempo de resposta para execução de tarefas:**  
    Medir o tempo entre o comando de reprodução e o início do áudio.  
    - **Valor medido:** [....................................................]
  - **Tempo de inicialização do módulo:**  
    Medir o tempo para o módulo estar pronto após o boot.  
    - **Valor medido:** [....................................................]
  - **Tempo de comunicação entre módulos:**  
    Avaliar o tempo de resposta a comandos vindos de outras tarefas.  
    - **Valor medido:** [....................................................]
  - **Tempo de processamento de dados recebidos:**  
    Medir o tempo de processamento dos comandos de controle do módulo.  
    - **Valor medido:** [....................................................]

---

> **Observação:**  
> Para todas as medições de tempo, utilize funções como `millis()`, `micros()` ou ferramentas de profiling do ESP32. Para medições de memória, utilize funções do framework ESP-IDF/Arduino. Registre todos os resultados em logs para análise posterior.
