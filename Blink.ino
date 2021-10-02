// Define the array of leds
// CRGB blinkLeds[NUM_LEDS];

void blinkSetup() {
    FastLED.addLeds<WS2811, DATA_PIN, GRB>(globalLedsArr, NUM_LEDS);
}

void blinkLoop() { 
  // Turn the LED on, then pause
  globalLedsArr[1] = CRGB::Red;
  FastLED.show();
  if(sleep(500)) return;
  // Now turn the LED off, then pause
  globalLedsArr[1] = CRGB::Black;
  FastLED.show();
  if(sleep(500)) return;
}
