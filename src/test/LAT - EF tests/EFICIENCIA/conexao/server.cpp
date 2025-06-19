#include "server.h"
#include "../sensores/hc_sr04.h"
#include "../sensores/mq135.h"
#include "../sensores/hx711.h"

WebServer servidor(SERVER_PORT);

void handleRoot() {
    String json = "{";
    json += "\"distanciaInternaCM\":" + String(distanciaInternaCM) + ",";
    json += "\"distanciaExternaCM\":" + String(distanciaExternaCM) + ",";
    json += "\"mqValorAnalogico\":" + String(mqValorAnalogico) + ",";
    json += "\"mqGasDetectado\":" + String(mqGasDetectado ? "true" : "false") + ",";
    json += "\"hx711Peso\":" + String(hx711Peso);
    json += "}";
    
    servidor.sendHeader("Access-Control-Allow-Origin", "*");
    servidor.send(200, "application/json", json);
}

void initServer() {
    servidor.on("/", HTTP_GET, handleRoot);
    servidor.begin();
    Serial.println("Servidor web iniciado!");
}