
#include <ESP8266WiFi.h> 
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


const char* ssid = "armandt";
const char* password = "NgfyoiGl19";
int estadoAnterior;
int estadoActual;
int izq;
int der;

 
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
  estadoActual = digitalRead(5);
  if(estadoAnterior!=estadoActual){
    estadoAnterior = estadoActual;
    estadoAnterior = estadoActual;
     izq = digitalRead(4);
     der = digitalRead(5);
    post("izq",izq);
    post("der",der);
  }else{
    delay(1000);
  }
}

void post(String nombre,int estado) {
  HTTPClient http;
  String json;
  String server = "http://192.168.1.85:3300/interruptores/";

  StaticJsonDocument<256> doc;
  doc["nombre"] = (nombre);
  doc["estado"] = (estado);
  serializeJson(doc, json);

  http.begin(server);
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
  Serial.println("");
}
