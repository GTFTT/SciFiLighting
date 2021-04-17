// Define the array of leds
CRGB justBlueLeds[NUM_LEDS];

void justBlueSetup() {
    FastLED.addLeds<WS2811, DATA_PIN, GRB>(justBlueLeds, NUM_LEDS);
}

void justBlueLoop() { 
  for(int i = 0; i < NUM_LEDS; i++) {
    justBlueLeds[i] = CRGB::Blue;
  }
  
  FastLED.show();

  if(sleep(100)) return;
}
