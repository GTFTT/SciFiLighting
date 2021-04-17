// Define the array of leds
CRGB justLightLeds[NUM_LEDS];

void justLightSetup() {
    FastLED.addLeds<WS2811, DATA_PIN, GRB>(justLightLeds, NUM_LEDS);
}

void justLightLoop() { 
  for(int i = 0; i < NUM_LEDS; i++) {
    justLightLeds[i] = CRGB::White;
  }
  
  FastLED.show();

  if(sleep(100)) return;
}
