#include <WiFi.h>
#include <WebServer.h>
#include <Arduino.h>

constexpr int maxRange = 30;
constexpr int minRange = 5;
constexpr int trigDelay = 10;
constexpr int numSamples = 5;

const int TRIG_1 = 33;
const int ECHO_1 = 32;
const int RED_1 = 12;
const int YELLOW_1 = 14;
const int GREEN_1 = 27;

const int TRIG_2 = 25;
const int ECHO_2 = 13;
const int RED_2 = 26;
const int GREEN_2 = 35;

const char *ssid = "Exploda";
const char *password = "***********"; // TODO: password xd

WebServer server(80);

long microSecondsToCentimeters(long microSeconds)
{
    return microSeconds / 29 / 2;
}

long singleReadCM(int trigPin, int echoPin)
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(trigDelay);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH, 30000);
    return microSecondsToCentimeters(duration);
}

long readDistanceAvgCM(int trigPin, int echoPin)
{
    long sum = 0;
    int validReads = 0;
    for (int i = 0; i < numSamples; i++)
    {
        long d = singleReadCM(trigPin, echoPin);
        if (d > 0 && d < 400)
        {
            sum += d;
            validReads++;
        }
        delay(5); // reduzido para resposta mais rápida
    }
    return (validReads > 0) ? sum / validReads : 0;
}

void handleRoot()
{
    long cm1 = readDistanceAvgCM(TRIG_1, ECHO_1);
    delay(5);
    long cm2 = readDistanceAvgCM(TRIG_2, ECHO_2);

    String json = "{";
    json += "\"sensor1\":" + String(cm1) + ",";
    json += "\"sensor2\":" + String(cm2) + "}";
    /*
    {
    "sensor1": xCm,
    "sensor2": xCm,
    "peso": xg / kg
    "amonia": xppm
    }
    */

    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "GET");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
    server.send(200, "application/json", json);

    // LED Sensor 1
    digitalWrite(RED_1, cm1 < minRange);
    digitalWrite(YELLOW_1, cm1 >= minRange && cm1 < maxRange);
    digitalWrite(GREEN_1, cm1 >= maxRange);

    // LED Sensor 2
    digitalWrite(RED_2, !(cm2 > 0 && cm2 < maxRange));
    digitalWrite(GREEN_2, cm2 > 0 && cm2 < maxRange);
}

void setupWiFi()
{
    WiFi.begin(ssid, password);
    Serial.print("Conectando-se ao WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi conectado. IP: ");
    Serial.println(WiFi.localIP());
}

void setup()
{
    Serial.begin(9600);

    pinMode(TRIG_1, OUTPUT);
    pinMode(ECHO_1, INPUT);
    pinMode(RED_1, OUTPUT);
    pinMode(YELLOW_1, OUTPUT);
    pinMode(GREEN_1, OUTPUT);

    pinMode(TRIG_2, OUTPUT);
    pinMode(ECHO_2, INPUT);
    pinMode(RED_2, OUTPUT);
    pinMode(GREEN_2, OUTPUT);

    setupWiFi();
    server.on("/", HTTP_GET, handleRoot);
    server.begin();
    Serial.println("Servidor iniciado.");
}

void loop()
{
    server.handleClient();
}