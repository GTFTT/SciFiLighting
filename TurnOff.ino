void turnOffSetup() {
}

void turnOffLoop() { 
  for(int i = 0; i < NUM_LEDS; i++) {
    globalLedsArr[i] = CRGB::Black;
  }
  
  FastLED.show();

  if(sleep(100)) return;
}
