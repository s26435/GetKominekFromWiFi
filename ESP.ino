#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

SoftwareSerial ESP8266(D2, D3);

void setup(){
	Serial.begin(9600);
	ESP8266.begin(4800);
	pinMode(D2,INPUT);
	pinMode(D4, OUTPUT);
}

void loop(){
	ESP8266.print("10");
	ESP8266.println("\n");
	delay(30);
}