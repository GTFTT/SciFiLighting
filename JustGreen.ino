void justGreenSetup() {
}

void justGreenLoop() { 
  for(int i = 0; i < NUM_LEDS; i++) {
    globalLedsArr[i] = CRGB::Green;
  }
  
  FastLED.show();

  if(sleep(100)) return;
}
