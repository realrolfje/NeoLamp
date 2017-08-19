// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            3

// How many NeoPixels are attached to the Arduino?
const byte  NUMPIXELS    =  10;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  Serial.begin(9600);// open the serial port at 9600 bps
  Serial.println("\n\n----------- START -------------------");

    /* Initialize pixels and clear if they were already on */
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void loop() {  
  // Start with a rainbow
  for(int i=0; i< NUMPIXELS; i++) {
    uint32_t color = wheel(((i * 256 / NUMPIXELS))& 255);
    setTargetColor(i, color);
  }
  transform(7);

  // Then turn on the white light
  migrateAllTo(10, pixels.Color(0,0,0,255));

  delay(5000);
  migrateAllTo(5, pixels.Color(0,0,0,0)); 
  delay(1000);
}

