void justLightSetup() {
}

void justLightLoop() { 
  for(int i = 0; i < NUM_LEDS; i++) {
    globalLedsArr[i] = CRGB::White;
  }
  
  FastLED.show();

  if(sleep(100)) return;
}
