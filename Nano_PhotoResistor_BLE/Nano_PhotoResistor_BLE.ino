#include <SoftwareSerial.h>
SoftwareSerial espSerial(12, 11); 
const int lightPin = A1; // Пін, до якого підключено фоторезистор

void setup() {
  Serial.begin(9600);  
  espSerial.begin(9600); 
  pinMode(lightPin, INPUT);
}

void loop() {
  int lightValue = analogRead(lightPin); 
  Serial.print("Рівень освітленості: ");
  Serial.println(lightValue);
  espSerial.println(lightValue); 
  delay(1000); 
}