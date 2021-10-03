// Define the array of leds
// CRGB justGreenLeds[NUM_LEDS];

void justGreenSetup() {
    // FastLED.addLeds<WS2811, DATA_PIN, GRB>(globalLedsArr, NUM_LEDS);
}

void justGreenLoop() { 
  for(int i = 0; i < NUM_LEDS; i++) {
    globalLedsArr[i] = CRGB::Green;
  }
  
  FastLED.show();

  if(sleep(100)) return;
}
