// Yellow strip moving through strips
// Assume strip length is 20
int presetWaiting(byte tick, uint16_t ledCount, CRGB* leds) {
  byte ledToLight = tick % 25;
  for (uint16_t i = 0; i < ledCount; i++) {
    if (i % 20 == ledToLight) {
      leds[i] = CRGB(255, 0, 255);
    } else {
      leds[i] = CRGB(0, 0, 0);
    }
  }
  return 0;
}
