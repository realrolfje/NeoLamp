
/* 
 * Colors are stored as separate bytes because storing them as uint32_t in an array triggers this problem:
 * https://stackoverflow.com/questions/39255127/arduino-error-unable-to-find-a-register-to-spill-in-class-no-regs#39257488
 */
byte targetColors[NUMPIXELS*4];

/*
 * Sets the target color for the pixel to migrate to later.
 */
void setTargetColor(int pixel, uint32_t color){
  if (pixel >=0 && pixel < NUMPIXELS) {
    for (int i=0; i<4; i++) {
      targetColors[pixel*4 + i] = color & 0xFF;
      color = color >> 8;
    }
  }
}

/*
 * Gets the target color at the specified index. This needs to be done
 * the hard way because we can not have arrays of int32_t for some reason.
 */
uint32_t getTargetColor(int pixel){
  if (pixel >=0 && pixel < NUMPIXELS) {
    uint32_t color = 0;
    for (int i=3; i>=0; i--) {
        color = color << 8;
        color = color | ((unsigned) targetColors[pixel*4 + i]);
    }
    return color;
  } else return 0;
}

/*
 * Slowly changes all pixels to the given target color.
 */
void migrateAllTo(int stepDelay, uint32_t targetColor) {
  for(int i=0; i < NUMPIXELS; i++) {
    setTargetColor(i, targetColor);
  }
  transform(stepDelay);
}

/*
 * Slowly changes current pixel color to the colors
 * in the targetPixel array.
 */
void transform(int stepDelay) {
  Serial.println("Begin transformation");
  boolean migrating = true;
  while (migrating) {
    migrating = false;
    for(int i=0; i< NUMPIXELS; i++) {
      migrating = stepToColor(i, getTargetColor(i)) || migrating;
    }
    pixels.show();   
    delay(stepDelay);
  }
}

boolean stepToColor(int pixelIndex, uint32_t targetColor) {
  byte targetRed   = (targetColor & 0xFF000000) >> 24;
  byte targetGreen = (targetColor & 0x00FF0000) >> 16;
  byte targetBlue  = (targetColor & 0x0000FF00) >> 8;
  byte targetWhite = (targetColor & 0x000000FF) >> 0;
  
  uint32_t currentColor = pixels.getPixelColor(pixelIndex);

  byte red   = (currentColor & 0xFF000000) >> 24;
  byte green = (currentColor & 0x00FF0000) >> 16;
  byte blue  = (currentColor & 0x0000FF00) >> 8;
  byte white = (currentColor & 0x000000FF) >> 0;

  if (red < targetRed)     {red++;}   else if (red>targetRed)     {red--;};
  if (green < targetGreen) {green++;} else if (green>targetGreen) {green--;};
  if (blue < targetBlue)   {blue++;}  else if (blue>targetBlue)   {blue--;};
  if (white < targetWhite) {white++;} else if (white>targetWhite) {white--;};

  uint32_t newColor = red;
  newColor = (newColor << 8) | green;
  newColor = (newColor << 8) | blue;
  newColor = (newColor << 8) | white;

  pixels.setPixelColor(pixelIndex, newColor);

  return newColor != targetColor;
}


