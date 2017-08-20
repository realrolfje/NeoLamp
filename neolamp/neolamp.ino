// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include <Adafruit_NeoPixel.h>

/* NeoPixel Serial data out. */
#define NEOPIXEL_DATAPIN            3

// How many NeoPixels are attached to the Arduino?
const byte  NUMPIXELS    =  10;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_DATAPIN, NEO_GRBW + NEO_KHZ800);

const uint32_t white = pixels.Color(100,0,0,127);

void setup() {
  Serial.begin(9600);// open the serial port at 9600 bps
  Serial.println("\n\n----------- START -------------------");

  pinMode(LED_BUILTIN, OUTPUT);

  // Seed random generator to get fresh patterns at each boot.
  randomSeed(analogRead(A0) * analogRead(A1) * analogRead(A2));

  /* Initialize pixels and clear if they were already on */
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void flipLed(){
  boolean led = digitalRead(LED_BUILTIN);
  digitalWrite(LED_BUILTIN, !led);
}

void loop() {  
  // Slowly start with a rotating rainbow
  byte rainbowOffset = 200;
  for (int j=0; j<255; j++) {
    for(int i=0; i< NUMPIXELS; i++) {
      uint32_t color = wheel(((i * 256 / NUMPIXELS) + j + rainbowOffset) & 255);
      color = brightness(j, color);
      setTargetColor(i, color);
    }
    showTargetColors();
    pixels.show();
    delay(5);
  }

  // Then turn on the white light
  migrateAllTo(15, white);

  // Select a random pixel and color
  while(true) {

    delay(random(7000, 14000));
    flipLed();

    if (random(100) < 1) {
      // Rainbow with a chance of one in 100
      Serial.println("Rainbow!");
      byte rainbowOffset =  round(255);
      for(int i=0; i< NUMPIXELS; i++) {
        uint32_t color = wheel(((i * 256 / NUMPIXELS) + rainbowOffset) & 255);
        setTargetColor(i, color);
      }
      transform(20);
      delay(1000);
    } else {
      // One sneaky color.
      Serial.println("Sneaky pixel.");
      byte pixel = random(0,9);
      byte color = random(0,255);
      setTargetColor(pixel, wheel(color));
      transform(20);
      delay(random(2000, 14000));
    }

    Serial.println("White.");
    migrateAllTo(20, white);
  }
}

