
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const int maxRange = 30;
const int minRange = 5;

const int TRIG = 26;
const int ECHO = 25;

const int red = 12;
const int yellow = 14;
const int green = 27;

// ? Local Network
const char *local_ssid = "Visitantes";
const char *local_pass = "";

// ? Client Connection
const char *ssid = "ESP32-Network";
const char *password = "0123456789";

// ? Set web server port number to 80
WiFiServer server(80);

// ? Var to store the HTTP request
String header;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void setup()
{
    Serial.begin(9600);
    WiFi.softAP(ssid, password);
    // ? Print IP address and start web server
    Serial.println("");
    Serial.println("IP address: ");
    Serial.println(WiFi.softAPIP());
    server.begin();
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);
}

long microSecondsToInches(long microSeconds) { return microSeconds / 74 / 2; }

long microSecondsToCentimeters(long microSeconds) { return microSeconds / 29 / 2; }

void loop()
{
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

    WiFiClient client = server.available();

    if (client)
    {
        currentTime = millis();
        previousTime = currentTime;
        Serial.println("New Client.");
        String currentLine = "";

        while (client.connected() && currentTime - previousTime <= timeoutTime)
        {
            // ? loop while the client's connected
            currentTime = millis();
            if (client.available())
            {
                char c = client.read();
                Serial.write(c);
                header += c;
                if (c == '\n')
                {
                    if (currentLine.length() == 0)
                    {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        // ? HTML page
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        // Display the HTML web page
                        client.println("<!DOCTYPE html><html lang=\"pt-br\" xml:lang=\"pt-br\">");
                        client.println("<head><meta charset=\"UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <title>ESP32 Web Server</title>");
                        client.println("<body><h1>ESP32 Web Server</h1>");

                        Serial.print(inches);
                        Serial.print("in, ");
                        Serial.print(cm);
                        Serial.print("cm");
                        Serial.println();

                        if (cm >= maxRange)
                        {
                            digitalWrite(red, LOW);
                            digitalWrite(yellow, LOW);
                            digitalWrite(green, HIGH);
                            client.println("<p>vazio = _ =)</p>");
                        }
                        else if (cm < maxRange && cm >= minRange)
                        {
                            digitalWrite(red, LOW);
                            digitalWrite(green, LOW);
                            digitalWrite(yellow, HIGH);
                            client.println("<p>meio cheio ou meio vazio???!?!!</p>");
                        }
                        else
                        {
                            digitalWrite(yellow, LOW);
                            digitalWrite(green, LOW);
                            digitalWrite(red, HIGH);
                            client.println("<p>CHEIO!</p>");
                        }

                        client.println("</body></html>");

                        // The HTTP response ends with another blank line
                        client.println();
                        // Break out of the while loop
                        break;
                    }
                    else
                    {
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {
                    currentLine += c;
                }
            }
        }
        header = "";
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}
