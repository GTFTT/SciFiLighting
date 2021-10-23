void justBlueSetup() {
}

void justBlueLoop() { 
  for(int i = 0; i < NUM_LEDS; i++) {
    globalLedsArr[i] = CRGB::Blue;
  }
  
  FastLED.show();

  if(sleep(100)) return;
}
