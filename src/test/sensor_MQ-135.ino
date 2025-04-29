
#define MQ2pin 5 // porta 5 no ESP32

int sensorValue; // variável que vai guardar o valor do sensor

void setup()
{
  Serial.begin(9600);
  Serial.println("Aquecendo o sensor MQ2");
  delay(200); // tempo de aquecimento (na vida real são alguns minutos para o sensor aquecer)
}

void loop()
{
  sensorValue = digitalRead(MQ2pin); // lê a porta 8
                                     // MQ2pin → Retorna 1 se não houver gás detectado | Retorna 0 se houver gás

  Serial.print("Digital Output: ");
  Serial.print(sensorValue);

  if (sensorValue)
  {
    Serial.println(" | Nenhum gás detectado - ");
  }
  else
  {
    Serial.println(" | Gás Detectado!");
  }

  delay(2000);
}