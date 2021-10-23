// Define the array of leds
// CRGB turnOffLeds[NUM_LEDS];

void turnOffSetup() {
    // FastLED.addLeds<WS2811, DATA_PIN, GRB>(globalLedsArr, NUM_LEDS);
}

void turnOffLoop() { 
  for(int i = 0; i < NUM_LEDS; i++) {
    globalLedsArr[i] = CRGB::Black;
  }
  
  FastLED.show();

  if(sleep(100)) return;
}
