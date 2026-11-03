#include <Adafruit_NeoPixel.h>
#include "pitches.h"

#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_PIN 26 // Which pin on the Arduino is connected to the NeoPixels?
#define LED_COUNT 4 // How many NeoPixels are attached to the Arduino?
int buzzerPin = 25;
int melody[] = {
  NOTE_C5, NOTE_C5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_A5, NOTE_G5,
  NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_C5,
  NOTE_G5, NOTE_G5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_D5,
  NOTE_G5, NOTE_G5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_D5,
  NOTE_C5, NOTE_C5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_A5, NOTE_G5,
  NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_C5
};

// Note durations: 4 = quarter note, 8 = eighth note, 16 = sixteenth note, etc.
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4
};



Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Declare our NeoPixel strip object:
void setup() {
  #ifdef __AVR__
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  strip.begin();           
  strip.show();            
  strip.setBrightness(50); 
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {

    int noteFrequency = melody[i];
    int noteDuration = 1000 / noteDurations[i];
    tone(buzzerPin, noteFrequency, noteDuration);
    delay(noteDuration * 1.3);
  }
}

void loop() {
  
    byte r = random(0, 256);
    byte g = random(0, 256);
    byte b = random(0, 256);
    for (int i = 0; i < LED_COUNT; i++) {
      
      strip.setPixelColor(i, strip.Color(r, g, b));
      strip.show(); 
      delay(200);  
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.show(); 
      delay(200);   
    }
}