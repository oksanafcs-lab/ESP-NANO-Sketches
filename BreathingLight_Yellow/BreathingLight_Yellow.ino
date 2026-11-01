const int ledPin = 26;
int step = 5;
int delayTime = 50;
void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  for (int i = 0; i<255; i=i+step) {
    analogWrite(ledPin, i); 
    delay(delayTime); 
  }
  for (int i = 255; i>0; i=i-step) {
    analogWrite(ledPin, i); 
    delay(delayTime); 
  }
}
