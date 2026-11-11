#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int sensorPin = A0;
const int soilSensorPin = A2;
const int mosfetPin = 11;
//calibration
int minValue = 36;
int maxValue = 643;
void setup() {
  lcd.init();      
  lcd.backlight();
  pinMode(mosfetPin, OUTPUT);
}

void loop() {
  //lcd.clear();
  int soilValue = analogRead(soilSensorPin);
  int lightValue = analogRead(sensorPin);
  lcd.setCursor(0, 0);
  lcd.print("Soil:          ");
  lcd.setCursor(7, 0);
  lcd.print(soilValue);
  if (soilValue < 150) {
  	digitalWrite(mosfetPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Motor ON ");
  } else {
  	digitalWrite(mosfetPin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Motor OFF");
  }
  /*lcd.print("Light level:    ");
  lcd.setCursor(13, 0);
  lcd.print(lightValue);
  int constrainedValue = constrain(lightValue, minValue, maxValue);
  float lightIntensity = (float)(constrainedValue - minValue) * 100.0 / 
                         (maxValue - minValue);  
  lcd.setCursor(1, 1);
  lcd.print("                ");
  lcd.setCursor(1, 1);
  lcd.print(lightIntensity);
  lcd.setCursor(8, 1);
  lcd.print("%");
  delay(500);*/
}
