#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11);

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  Serial.println("=== Конфігурація HC-06 ===");
  Serial.println("Відправте AT команди без нового рядка");
  Serial.println();

  delay(1000);

  // Тестуємо зв'язок
  Serial.println("Перевірка зв'язку...");
  bluetooth.print("AT");
  delay(1000);
  printResponse();

  // Запитуємо версію
  Serial.println("Запит версії...");
  bluetooth.print("AT+VERSION");
  delay(1000);
  printResponse();

  // Змінюємо ім'я
  Serial.println("Зміна імені...");
  bluetooth.print("HC-06");
  delay(1000);
  printResponse();

  // Встановлюємо PIN
  Serial.println("Встановлення PIN...");
  bluetooth.print("1234");
  delay(1000);
  printResponse();

  Serial.println();
  Serial.println("Конфігурація завершена!");
  Serial.println("Тепер модуль готовий до роботи");
}

void loop() {
  // Режим передачі AT команд вручну
  if (bluetooth.available()) {
    Serial.write(bluetooth.read());
  }
  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }
}

void printResponse() {
  Serial.print("Відповідь: ");
  while (bluetooth.available()) {
    Serial.write(bluetooth.read());
    delay(10);
  }
  Serial.println();
}