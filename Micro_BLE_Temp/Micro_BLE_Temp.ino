#include <DHT11.h>
#include <SoftwareSerial.h>

DHT11 dht11(6);

// Створюємо програмний порт для Bluetooth: пін 10 = RX (до TXD модуля), пін 11 = TX (до RXD модуля)
SoftwareSerial btSerial(10, 11);

void setup() {
  // USB-порт для виводу в Монітор порту ПК
  Serial.begin(9600); 
  
  // Програмний порт для відправки даних через Bluetooth-модуль
  btSerial.begin(9600);
}

void loop() {
  // Зчитування вологості та температури
  int temperature = dht11.readTemperature();
  int humidity = dht11.readHumidity();

  // Перевірка, чи немає помилок зчитування (у цій бібліотеці помилки мають коди помилок або високі значення)
  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT &&
      humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT) {
    
    // Формуємо рядок з даними
    String message = "Температура: " + String(temperature) + " °C , Вологість: " + String(humidity) + " %";

    // Відправка даних у Монітор порту ПК
    Serial.println(message);
    
    // Відправка даних через Bluetooth-модуль (на ESP32 або телефон)
    btSerial.println(message);
    
  } else {
    String errorMsg = DHT11::getErrorString(temperature);
    Serial.println(errorMsg);
    btSerial.println(errorMsg);
  }

  // Пауза 2 секунди (оптимально для DHT11)
  delay(2000);
}
