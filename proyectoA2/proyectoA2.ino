#include <DHT.h>

#include <ESP8266WiFi.h> 
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
const int x=5;
DHT dht(x, DHT11);

const int PIRPin= 4;

int a;
#define WIFISSID "InternetSelecto_5E6C"
#define PASS "cybernetmx20205E6C"

void setup() {
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
    dht.begin();
    pinMode(PIRPin, INPUT);
}

void loop() {    
   //post(a);
   delay(5000);
   float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }else{
    //post(t);
  }
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");

  int value= digitalRead(PIRPin);
 
  if (value == HIGH)
  {
    Serial.print(value);
  }
  else
  {
    Serial.print("error: ");
  }

  post(value,t);
}

void post(int a, double t) {
  HTTPClient http;
   WiFiClient client;
  String json;
  DynamicJsonDocument root(1024);
  root["nombre"] = "Interruptor 1";
  root["estado"] = a;
  root["temperatura"] = t;
  serializeJson(root, json);
  http.begin(client, "http://144.202.17.134:3320/Interruptores");
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
}
