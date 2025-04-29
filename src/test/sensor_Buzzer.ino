
const int pirPin = 15;   // Pino do sensor PIR
const int buzzerPin = 5; // Pino do buzzer

void setup()
{
  pinMode(pirPin, INPUT);     // Sensor como entrada
  pinMode(buzzerPin, OUTPUT); // Buzzer como saída
  Serial.begin(9600);
}

void loop()
{
  int pirState = digitalRead(pirPin); // Lê o sensor

  if (pirState == HIGH)
  {
    Serial.println("Movimento detectado!");
    digitalWrite(buzzerPin, HIGH); // Liga
    delay(500);                    // Buzina por meio segundo
    digitalWrite(buzzerPin, LOW);  // Desliga
    delay(500);                    // Espera meio segundo
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
  }
}