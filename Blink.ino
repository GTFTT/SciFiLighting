void blinkSetup() {
  for(int i = 0; i < NUM_LEDS; i++) {
    globalLedsArr[i] = CRGB::Black;
  }
  
  FastLED.show();
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
