#define BLYNK_TEMPLATE_ID My_TEMPLATE_ID;
#define BLYNK_TEMPLATE_NAME My_TEMPLATE_NAME;
#define BLYNK_AUTH_TOKEN My_AUTH_TOKEN;
#include "secretData.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "BluetoothSerial.h"
char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASS;
#define RXD2 16 // Використовуємо апаратний Serial2 на ESP32
#define TXD2 17 // (RX2 = GPIO 16, TX2 = GPIO 17)
#define steam 34
BlynkTimer timer;
BluetoothSerial SerialBT;
String slaveName = "HC-06"; // Ім'я модуля на Arduino Micro
String pin = "1234";        // PIN-код HC-06

void checkSerialData() {
  if (Serial2.available() > 0) { // Зчитуємо рядок від Arduino Nano
  String data = Serial2.readStringUntil('\n');
  data.trim(); // Видаляємо зайві пробіли
  if (data.length() > 0) {
    int lightValue = data.toInt();
    // Відправляємо значення на віртуальний пін V1 у Blynk
    Blynk.virtualWrite(V0, lightValue);// дані з ардуіно нано, передані через RX/TX
    Serial.print("Light: ");
    Serial.println(lightValue);
    int steam_val = analogRead(steam);
    int steamPercent = map(steam_val, 0, 4095, 0, 100);
    Serial.print("Steam: ");
    Serial.println(steamPercent);
    Blynk.virtualWrite(V2, steamPercent);//дані напряму з ESP32
  }
 }
}
void checkBluetoothData() {
  // Перевірка з'єднання з HC-06
  if (!SerialBT.connected()) {
    Serial.println("HC-06 не підключено. Спроба підключення...");
    SerialBT.connect(slaveName);
    return;
  }
  if (SerialBT.available() > 0) {
    String btData = SerialBT.readStringUntil('\n');
    btData.trim();
    int firstColon = btData.indexOf(':');
    int secondColon = btData.indexOf(':', firstColon + 1);

    if (firstColon > 0 && secondColon > 0) {
      int temp = btData.substring(firstColon + 1).toInt();
      int hum = btData.substring(secondColon + 1).toInt();
      Serial.print("Розпарсено -> Temp (V1): ");
      Serial.print(temp);
      Serial.print(" °C, Hum (V3): ");
      Serial.print(hum);
      Serial.println(" %");
    

      // Відправляємо у Blynk на віртуальні піни V3 та V4
      Blynk.virtualWrite(V1, temp);
      Blynk.virtualWrite(V3, hum);
      
    }
  }
}
void setup() {
 Serial.begin(115200); // Для відладки
// Ініціалізація Serial2 для зв'язку з Nano
 Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
// Запуск Bluetooth у режимі Master для підключення до HC-06
  SerialBT.begin("ESP32_Master", true);
  SerialBT.setPin(pin.c_str(), pin.length());
  SerialBT.connect(slaveName);
 // Підключення до Blynk
 Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
 // Налаштування таймера на перевірку
 //даних кожні 500 мс
 timer.setInterval(1000L, checkSerialData);
 timer.setInterval(1000L, checkBluetoothData);
}
void loop() {
 Blynk.run();
 timer.run();
}
