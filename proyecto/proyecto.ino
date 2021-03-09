//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
//#include <ArduinoJson.h>
#include <ESP8266WiFi.h> 
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>
 
// Definimos el pin digital donde se conecta el interruptor
#define DHTPIN 2

//#include "config.h"  // Sustituir con datos de vuestra red
//#include "API.hpp"
//#include "ESP8266_Utils.hpp"

const char* ssid = "InternetSelecto_5E6C";
const char* password = "cybernetmx20205E6C";
const char* host = "192.168.1.104";
int estadoAnterior;
int estadoActual;

 
void setup () {
  Serial.begin(115200);
  delay(10);
 
  // Conectamos a la red WiFi
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  /* Configuramos el ESP8266 como cliente WiFi. Si no lo hacemos 
     se configurará como cliente y punto de acceso al mismo tiempo */
  WiFi.mode(WIFI_STA); // Modo cliente WiFi
  WiFi.begin(ssid, password);
 
  // Esperamos a que estemos conectados a la red WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  estadoAnterior = digitalRead(5);
}
 
void loop() {
  
 
  WiFiClient client;
  const int httpPort = 3132; // Puerto HTTP
  if (!client.connect(host, httpPort)) {
    // ¿hay algún error al conectar?
    Serial.println("Ha fallado la conexión");
    return;
  }else{
    estadoActual = digitalRead(5);
    if(estadoAnterior!=estadoActual){
      estadoAnterior = estadoActual;
      post();
    }else{
      delay(1000);
    }
  }
  
 
}

void post() {
  HTTPClient http;
  String json;
  String server = "http://192.168.1.104:3132/interruptores";
  int t = digitalRead(2);

  StaticJsonDocument<256> doc;
  doc["interruptor"] = (t);
  serializeJson(doc, json);
  
  http.begin(server);
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
  Serial.println("");
}
