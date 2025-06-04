#include <Arduino.h>
#include <WiFi.h>

#define TRIG_PIN 26
#define ECHO_PIN 25

const int maxRange = 30;
const int minRange = 5;

long duration, cm;

#define RED_PIN 12
#define YELLOW_PIN 14
#define GREEN_PIN 27

const char *ssid = "ESP32-Network";
const char *password = "0123456789";

WiFiServer server(80);

const long timeoutTime = 2000;
const int BLINK_DELAY = 100;

TaskHandle_t Task1Handle = NULL;
TaskHandle_t Task2Handle = NULL;

long microSecondsToInches(long microSeconds)
{
    return microSeconds / 74 / 2;
}

long microSecondsToCentimeters(long microSeconds)
{
    return microSeconds / 29 / 2;
}

void Task1(void *pvParameters)
{
    for (;;)
    {
        digitalWrite(TRIG_PIN, LOW);
        ets_delay_us(4);
        digitalWrite(TRIG_PIN, HIGH);
        ets_delay_us(20);
        digitalWrite(TRIG_PIN, LOW);
        duration = pulseIn(ECHO_PIN, HIGH);
        cm = microSecondsToCentimeters(duration);
        Serial.print(cm);
        Serial.print("cm");
        Serial.println();
        bool red = false, yellow = false, green = false;
        if (cm >= maxRange)
        {
            green = true;
        }
        else if (cm >= minRange)
        {
            yellow = true;
        }
        else
        {
            red = true;
        }
        digitalWrite(RED_PIN, red);
        digitalWrite(YELLOW_PIN, yellow);
        digitalWrite(GREEN_PIN, green);
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}

void Task2(void *pvParameters)
{
    for (;;)
    {
        WiFiClient client = server.available();
        if (client)
        {
            unsigned long startTime = millis();
            String header = "";
            String currentLine = "";

            while (client.connected() && (millis() - startTime <= timeoutTime))
            {
                if (client.available())
                {
                    char c = client.read();
                    header += c;
                    if (c == '\n')
                    {
                        if (currentLine.length() == 0)
                        {
                            client.println("HTTP/1.1 200 OK");
                            client.println("Content-type:text/html");
                            client.println("Connection: close");
                            client.println();
                            int percent = 0;
                            if (cm <= minRange)
                            {
                                percent = 100;
                            }
                            else if (cm >= maxRange)
                            {
                                percent = 0;
                            }
                            else
                            {
                                percent = 100 - ((cm - minRange) * 100 / (maxRange - minRange));
                            }
                            String status = (percent >= 100) ? "Cheia" : "Disponível";
                            client.println("<!DOCTYPE html><html lang=\"pt-br\">"
                                           "<head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                                           "<title>ESP32 Web Server</title></head>"
                                           "<body><h1>ESP32 Web Server</h1>");
                            client.print("<p>Porcentagem de ocupação: <b>");
                            client.print(percent);
                            client.println("%</b></p>");
                            client.print("<p>Status: <b>");
                            client.print(status);
                            client.println("</b></p>");
                            client.println("</body></html>");
                            client.println();
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
            client.stop();
        }
        vTaskDelay(10 / portTICK_PERIOD_MS); // Pequeno delay para evitar loop apertado
    }
}

void setup()
{
    Serial.begin(9600);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    pinMode(RED_PIN, OUTPUT);
    pinMode(YELLOW_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);

    // Teste dos LEDs
    Serial.println("\nTest leds");
    for (int PIN : {RED_PIN, YELLOW_PIN, GREEN_PIN})
    {
        Serial.print("LED: ");
        Serial.println(PIN);
        digitalWrite(PIN, HIGH);
        delay(BLINK_DELAY);
        digitalWrite(PIN, LOW);
        delay(BLINK_DELAY);
    }

    WiFi.softAP(ssid, password);
    Serial.println("\nIP address: ");
    Serial.println(WiFi.softAPIP());
    server.begin();

    xTaskCreate(Task1, "Task1", 2048, NULL, 1, &Task1Handle);
    xTaskCreate(Task2, "Task2", 2048, NULL, 1, &Task2Handle);
}

void loop()
{
    // Tasks independentes
}
