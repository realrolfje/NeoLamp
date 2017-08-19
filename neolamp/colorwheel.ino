/*
 * Returns one of 255 colors arranged in a rainbouw pattern.
 * The rainbow pattern is arranged in transitions between the
 * colors green - red - blue (and back to green).
 * See https://learn.adafruit.com/florabrella/test-the-neopixel-strip
 */
uint32_t wheel(byte wheelPos) {
  if(wheelPos < 85) {
    // First third moves from Green to Red
    return pixels.Color(wheelPos * 3, 255 - wheelPos * 3, 0);
  } else if(wheelPos < 170) {
    // Second third moves from Red to Blue
    wheelPos -= 85;
    return pixels.Color(255 - wheelPos * 3, 0, wheelPos * 3);
  } else {
    // Second third moves from Blue to Green
    wheelPos -= 170;
    return pixels.Color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
}
