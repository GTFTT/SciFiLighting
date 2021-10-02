// Define the array of leds
// CRGB justLightLeds[NUM_LEDS];

void justLightSetup() {
    FastLED.addLeds<WS2811, DATA_PIN, GRB>(globalLedsArr, NUM_LEDS);
}

void justLightLoop() { 
  for(int i = 0; i < NUM_LEDS; i++) {
    globalLedsArr[i] = CRGB::White;
  }
  
  FastLED.show();

  if(sleep(100)) return;
}
