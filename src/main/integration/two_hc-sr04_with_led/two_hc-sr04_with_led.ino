
const int maxRange = 30;
const int minRange = 5;

const int TRIG = 33;
const int ECHO = 32;

const int red = 12;
const int yellow = 14;
const int green = 27;

const int TRIG_2 = 35;
const int ECHO_2 = 34;

const int red_2 = 26;
const int green_2 = 25;

void setup()
{
    Serial.begin(9600);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);

    pinMode(TRIG_2, OUTPUT);
    pinMode(ECHO_2, INPUT);

    pinMode(red_2, OUTPUT);
    pinMode(green_2, OUTPUT);
}

void loop()
{
    // Sensor 1
    long duration1, inches1, cm1;

    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    duration1 = pulseIn(ECHO, HIGH);

    inches1 = microSecondsToInches(duration1);
    cm1 = microSecondsToCentimeters(duration1);

    Serial.print("Sensor 1: ");
    Serial.print(inches1);
    Serial.print("in, ");
    Serial.print(cm1);
    Serial.print("cm | ");

    if (cm1 >= maxRange)
    {
        digitalWrite(red, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(green, HIGH);
    }
    else if (cm1 < maxRange && cm1 >= minRange)
    {
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
        digitalWrite(yellow, HIGH);
    }
    else
    {
        digitalWrite(yellow, LOW);
        digitalWrite(green, LOW);
        digitalWrite(red, HIGH);
    }

    // Sensor 2
    long duration2, inches2, cm2;

    digitalWrite(TRIG_2, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_2, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_2, LOW);

    duration2 = pulseIn(ECHO_2, HIGH);

    inches2 = microSecondsToInches(duration2);
    cm2 = microSecondsToCentimeters(duration2);

    Serial.print("Sensor 2: ");
    Serial.print(inches2);
    Serial.print("in, ");
    Serial.print(cm2);
    Serial.println("cm");

    // Acende green_2 se detectar objeto, senão acende red_2
    if (cm2 < maxRange && cm2 > 0)
    {
        digitalWrite(red_2, LOW);
        digitalWrite(green_2, HIGH);
    }
    else
    {
        digitalWrite(green_2, LOW);
        digitalWrite(red_2, HIGH);
    }

    delay(100);
}
