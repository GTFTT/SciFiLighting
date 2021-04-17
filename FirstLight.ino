///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.
// 

// This is an array of leds.  One item for each led in your strip.
CRGB firstLightLeds[NUM_LEDS];

// This function sets up the ledsand tells the controller about them
void firstLightSetup() {
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(firstLightLeds, NUM_LEDS);
}

// This function runs over and over, and is where you do the magic to light
// your leds.
void firstLightLoop() {
   // Move a single white led 
   for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
      // Turn our current led on to white, then show the leds
      firstLightLeds[whiteLed] = CRGB::White;

      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

      // Wait a little bit
      if(sleep(40)) return;

      // Turn our current led back to black for the next loop around
      firstLightLeds[whiteLed] = CRGB::Black;
   }

   //Move backward
   for(int whiteLed = NUM_LEDS-1; whiteLed >= 0; whiteLed = whiteLed - 1) {
      // Turn our current led on to white, then show the leds
      firstLightLeds[whiteLed] = CRGB::White;
      FastLED.show();
      
      if(sleep(100)) return;
      
      firstLightLeds[whiteLed] = CRGB::Black;
   }
}
