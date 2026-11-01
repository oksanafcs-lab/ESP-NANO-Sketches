#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_PIN 26 // Which pin on the Arduino is connected to the NeoPixels?
#define LED_COUNT 4 // How many NeoPixels are attached to the Arduino?
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Declare our NeoPixel strip object:
void setup() {
  #ifdef __AVR__
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  strip.begin();           
  strip.show();            
  strip.setBrightness(50); 
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