#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define btn1 16
#define btn2 27

void setup() {
  lcd.init();      
  lcd.backlight();
  lcd.clear();
  lcd.print("Press any button");
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
}

void loop() {
  boolean btn1_val = digitalRead(btn1);
  boolean btn2_val = digitalRead(btn2);
  if (!btn1_val){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hello, world!");
  }
  if (!btn2_val) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("UPD");
  }
}