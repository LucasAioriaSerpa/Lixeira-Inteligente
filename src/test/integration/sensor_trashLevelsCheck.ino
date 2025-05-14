
const int maxRange = 30;
const int minRange = 5;

const int TRIG = 14;
const int ECHO = 12;

const int red = 27;
const int yellow = 25;
const int green = 26;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

}

void loop() {
  // sensor
  long duration, inches, cm;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);

  inches = microSecondsToInches(duration);
  cm = microSecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  if (cm >= maxRange) {
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
  } else if (cm < maxRange && cm >= minRange) {
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
  } else {
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  }

  delay(100);

}

long microSecondsToInches(long microSeconds) { return microSeconds / 74 / 2; }

long microSecondsToCentimeters(long microSeconds) { return microSeconds / 29 / 2; }
