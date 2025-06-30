#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "SEU_SSID_AQUI";
const char* password = "SUA_SENHA_AQUI";

WebServer server(80);

const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>servidor ESP32</title>
</head>
<body style="font-family: arial; text-align: center; margin-top: 50px;">
<h1>ESP32 conectado com sucesso!</h1>
<p>Essa e uma pagina HTML enviada diretamente do seu ESP32.</p>
</body>
</html>
)rawliteral";

void setupWifiHtml() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  server.on("/", []() {
    server.send(200, "text/html", htmlPage);
  });

  server.begin();
}

void loopWifiHtml() {
  server.handleClient();
}