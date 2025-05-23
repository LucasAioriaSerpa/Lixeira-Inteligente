
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// ? Local Network
const char* local_ssid = "Visitantes";
const char* local_pass = "";

// ? Client Connection
const char* ssid     = "ESP32-Network";
const char* password = "0123456789";

// ? Set web server port number to 80
WiFiServer server(80);

// ? Var to store the HTTP request
String header;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid,password);
  // ? Print IP address and start web server
  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      // ? loop while the client's connected
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // ? HTML page
            client.println("""
<!DOCTYPE html>
<html lang=\"pt-br\" xml:lang=\"pt-br\">

<head>
    <meta charset=\"UTF-8\">
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">
    <title>ESP32 Web Server</title>
</head>
<style>
    * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
    }

    body {
        font-family: Arial, Helvetica, sans-serif;
        text-align: center;
        background-color: #f4f4f4;
    }

    h1 {
        color: #333333;
    }

    p {
        font-size: 20px;
        color: #666666;
    }
</style>

<body>
    <h1>ESP32 Web Server</h1>
    <p>Hello world</p>
</body>
<script>
    console.log(\"Hello from ESP32!\");
    // ? JavaScript code
    function showAlert() {
        alert(\"Hello from ESP32!\")
    }
</script>

</html>
            """);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
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