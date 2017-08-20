/*
 * Code to create a static or running rainbow on the pixels, for fun.
 */

void runningrainbow() {
  for (int j=0; j<256; j++) {
    rainbow(j);
    delay(15);    
  }
}

void rainbow(int startColorIndex){
    for(int i=0; i< NUMPIXELS; i++) {
      pixels.setPixelColor(i, wheel(((i * 256 / NUMPIXELS) + startColorIndex)& 255));
    }
    pixels.show();
}

