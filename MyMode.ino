#define PIXEL_CHANGE_DELAY 50
#define COLOR_CHANGE_DELAY 50

void myModeSetup() {
  for(int i = 0; i < NUM_LEDS; i++) {
    globalLedsArr[i] = CRGB::Black;
  }
  
  FastLED.show();
}

void myModeLoop() { 
  for(int i = 0; i < NUM_LEDS; i++) {
    globalLedsArr[i] = CRGB::Red;
    FastLED.show();
    if(sleep(PIXEL_CHANGE_DELAY)) return;
  }

  if(sleep(COLOR_CHANGE_DELAY)) return;

  for(int i = 0; i < NUM_LEDS; i++) {
    globalLedsArr[i] = CRGB::Green;
    FastLED.show();
    if(sleep(PIXEL_CHANGE_DELAY)) return;
  }

  if(sleep(COLOR_CHANGE_DELAY)) return;

  for(int i = 0; i < NUM_LEDS; i++) {
    globalLedsArr[i] = CRGB::Blue;
    FastLED.show();
    if(sleep(PIXEL_CHANGE_DELAY)) return;
  }

  if(sleep(COLOR_CHANGE_DELAY)) return;
}
