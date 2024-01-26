#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>

SoftwareSerial ES(D2, D3);
const char* ssid = "dupa";
const char* password = "dupadupa";
const char* serverName = "http://51.68.155.42:5000/info/1";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

String sensorReadings;
float sensorReadingsArr[3];

void setup(){
	WiFi.begin(ssid, password);
	Serial.begin(9600);
	ES.begin(4800);
	pinMode(D2,INPUT);
	pinMode(D4, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
float sensorReadingsArr[3];
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){      
      sensorReadings = httpGETRequest(serverName);
      Serial.println(sensorReadings);
      JSONVar myObject = JSON.parse(sensorReadings);
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
      Serial.print("JSON object = ");
      Serial.println(myObject);
      JSONVar keys = myObject.keys();
      for (int i = 0; i < keys.length(); i++) {
        JSONVar value = myObject[keys[i]];
        Serial.print(keys[i]);
        Serial.print(" = ");
        Serial.println(value);
        sensorReadingsArr[i] = double(value);
      }
      Serial.print("1 = ");
      Serial.println(sensorReadingsArr[0]);
      Serial.print("2 = ");
      Serial.println(sensorReadingsArr[1]);
      Serial.print("3 = ");
      Serial.println(sensorReadingsArr[2]);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, serverName);
  int httpResponseCode = http.GET();
  String payload = "{}"; 
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  return payload;
}
