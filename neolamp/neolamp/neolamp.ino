// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            3

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      10

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code


  pixels.begin(); // This initializes the NeoPixel library.
}


  byte R = 0;
  byte G = 0;
  byte B = 0;
  byte W = 0;
  int radR = 0;
  int radG = 0;
  int radB = 0;
  int radW = 0;

void loop() {
//  runningLights();
// CycleColors();
//  rainbow(0);
 runningrainbow();
}

void runningrainbow() {
  for (int j=0; j<256; j++) {
    rainbow(j);
    delay(15);    
  }
}

void runningLights(){
  while(true) {
    // Red
    for(int i=0; i<NUMPIXELS; i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(255,0,0,0));
      if (i==0) {
        pixels.setPixelColor(NUMPIXELS-1,pixels.Color(0,0,0,0));
      } else {
        pixels.setPixelColor(i-1,pixels.Color(0,0,0,0));
      }
      pixels.show();
      delay(100);
    }

    // Green
    for(int i=0; i<NUMPIXELS; i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0,255,0,0));
      if (i==0) {
        pixels.setPixelColor(NUMPIXELS-1,pixels.Color(0,0,0,0));
      } else {
        pixels.setPixelColor(i-1,pixels.Color(0,0,0,0));
      }
      pixels.show();
      delay(100);
    }

    // Blue
    for(int i=0; i<NUMPIXELS; i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0,0,255,0));
      if (i==0) {
        pixels.setPixelColor(NUMPIXELS-1,pixels.Color(0,0,0,0));
      } else {
        pixels.setPixelColor(i-1,pixels.Color(0,0,0,0));
      }
      pixels.show();
      delay(100);
    }

    // White
    for(int i=0; i<NUMPIXELS; i++){
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0,0,0,255));
      if (i==0) {
        pixels.setPixelColor(NUMPIXELS-1,pixels.Color(0,0,0,0));
      } else {
        pixels.setPixelColor(i-1,pixels.Color(0,0,0,0));
      }
      pixels.show();
      delay(100);
    }
  }
}

void rainbow(int startColorIndex){
    for(int i=0; i< NUMPIXELS; i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / NUMPIXELS) + startColorIndex)& 255));
    }
    pixels.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// From https://learn.adafruit.com/florabrella/test-the-neopixel-strip
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}



