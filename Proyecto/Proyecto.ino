#include <DHT.h>

#include <ESP8266WiFi.h> 
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const int triggerPin = 5; 
const int echoPin =4; 
long distancia, duracion; 

//DHT dht(14, DHT11);
const int sensorPin = 14;
int a;
#define WIFISSID "InternetSelecto_5E6C"
#define PASS "cybernetmx20205E6C"

void setup() {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFISSID, PASS);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    //dht.begin();
    pinMode(sensorPin , INPUT);
}

void loop() {    
   int distancia = ping(triggerPin, echoPin);
   //post(0);
   Serial.print("Distancia: ");
   Serial.println(distancia);
   delay(5000);
   
   int value = 0;
   value = digitalRead(sensorPin );
   Serial.println(value);
   if (value == HIGH) {
      Serial.println("Detectado obstaculo");
  }

  post(value,distancia);

  
}

int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distanceCm;
}

void post(int a, double t) {
  HTTPClient http;
   WiFiClient client;
  String json;
  DynamicJsonDocument root(1024);
  root["nombre"] = "Interruptor 2";
  root["estado"] = a;
  root["temperatura"] = t;
  serializeJson(root, json);
  http.begin(client, "http://144.202.17.134:3320/Interruptores");
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
}
