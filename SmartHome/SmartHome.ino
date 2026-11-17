#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT11 dht11(17);
//const
int btn_count = 0;
int menu_size = 3;
int pressCounter = 0;          // Лічильник натискань
int lastButtonState = HIGH;    // Попередній стан кнопки
unsigned long lastDebounceTime = 0;  // Час останньої зміни стану
unsigned long debounceDelay = 50;    // Затримка для захисту від брязкоту контактів (мс)

//Pins 
#define btn1 16
#define btn2 27
#define temp 17
#define steam 34

void setup() {
  lcd.init();      
  lcd.backlight();
  lcd.clear();
  lcd.print("Press Any Button ");
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
}

void loop() {

  boolean btn1_val = digitalRead(btn1);
   if (btn1_val != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    static int buttonState = HIGH;
    if (btn1_val != buttonState) {
      buttonState = btn1_val;

      if (buttonState == LOW) {
        btn_count++; 
        
      }
    }
  }
  handleButtonPress(btn_count);
  if (btn_count > menu_size) {
    btn_count = 0;
  }
  lastButtonState = btn1_val;
}
void handleButtonPress(int btn_count) {
  if (btn_count == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.setCursor(6, 0);
    int temperature = dht11.readTemperature();
    lcd.print(temperature);
    delay(300);
  }
  if (btn_count == 2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.setCursor(10, 0);
    int humidity = dht11.readHumidity();
    lcd.print(humidity);
    delay(300);
  }
  if (btn_count == 3) {
    int steam_val = analogRead(steam);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Moisture: ");
    lcd.setCursor(10, 0);
    lcd.print(steam_val);
    delay(300);
  }
  
}