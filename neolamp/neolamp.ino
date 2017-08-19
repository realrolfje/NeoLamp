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
//  Serial.begin(9600);// open the serial port at 9600 bps
  Serial.println("\n\n----------- START -------------------");

  
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
//  runningLights();
// CycleColors();
 pixels.clear();
 pixels.show();
 delay(1000);
 rainbow(0);
 migrateAllTo(pixels.Color(255,255,255,255));
 delay(1000);
 migrateAllTo(pixels.Color(0,0,0,0));
 delay(1000);
 
// runningrainbow();
}

void runningrainbow() {
  for (int j=0; j<256; j++) {
    rainbow(j);
    delay(15);    
  }
}

void migrateAllTo(uint32_t targetColor) {
  boolean migrating = true;
  while (migrating) {
    migrating = false;
    for(int i=0; i< NUMPIXELS; i++) {
      migrating = stepToColor(i, targetColor) || migrating;
    }
    pixels.show();   
    delay(5);
  }
}


boolean stepToColor(int pixelIndex, uint32_t targetColor) {
  byte targetRed   = (targetColor & 0xFF000000) >> 24;
  byte targetGreen = (targetColor & 0x00FF0000) >> 16;
  byte targetBlue  = (targetColor & 0x0000FF00) >> 8;
  byte targetWhite = (targetColor & 0x000000FF) >> 0;
  
  uint32_t currentColor = pixels.getPixelColor(pixelIndex);

  Serial.print("Current ");
  Serial.print(currentColor,HEX);

  byte red   = (currentColor & 0xFF000000) >> 24;
  byte green = (currentColor & 0x00FF0000) >> 16;
  byte blue  = (currentColor & 0x0000FF00) >> 8;
  byte white = (currentColor & 0x000000FF) >> 0;

  Serial.print(" RGBW ");
  Serial.print(red,HEX); Serial.print(" ");
  Serial.print(green,HEX); Serial.print(" ");
  Serial.print(blue,HEX); Serial.print(" ");
  Serial.print(white,HEX); Serial.print(" ");
  Serial.println();


  if (red < targetRed)     {red++;}   else if (red>targetRed)     {red--;};
  if (green < targetGreen) {green++;} else if (green>targetGreen) {green--;};
  if (blue < targetBlue)   {blue++;}  else if (blue>targetBlue)   {blue--;};
  if (white < targetWhite) {white++;} else if (white>targetWhite) {white--;};

  uint32_t newColor = red;
  newColor = (newColor << 8) | green;
  newColor = (newColor << 8) | blue;
  newColor = (newColor << 8) | white;

  pixels.setPixelColor(pixelIndex, newColor);

  Serial.print("New ");
  Serial.print(newColor,HEX);

  Serial.print(" RGBW ");
  Serial.print(red,HEX); Serial.print(" ");
  Serial.print(green,HEX); Serial.print(" ");
  Serial.print(blue,HEX); Serial.print(" ");
  Serial.print(white,HEX); Serial.print(" ");
  Serial.println();

  Serial.print("Target ");
  Serial.print(targetColor,HEX);

  Serial.print(" RGBW ");
  Serial.print(targetRed,HEX); Serial.print(" ");
  Serial.print(targetGreen,HEX); Serial.print(" ");
  Serial.print(targetBlue,HEX); Serial.print(" ");
  Serial.print(targetWhite,HEX); Serial.print(" ");
  Serial.println();

//  delay(1000);
//  while(true){};

  return newColor != targetColor;
}

void rainbow(int startColorIndex){
    for(int i=0; i< NUMPIXELS; i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / NUMPIXELS) + startColorIndex)& 255));
    }
    pixels.show();
    delay(10);
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



