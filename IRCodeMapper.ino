/*
 * This function chses mode based on a pressed button, it also launches corresponding setup method 
 * 
 * 
*/
void mapper(long long int code) {
  switch(code) {
      case 0xFFA857:
        Serial.println(F("Pressed Plus: Increase brightness"));
        increaseBrightness();
        break;

      case 0xFFE01F:
        Serial.println(F("Pressed Minus: Decrease brightness"));
        decreaseBrightness();
        break;
        
      case 0xFFC23D:
        Serial.println(F("Pressed Play/Pause: TurnOff"));
        turnOffSetup();
        currentMode = LightModes::TurnOff;
        break;
    
      case 0xFF6897:
        Serial.println(F("Pressed 0: Just light"));
        justLightSetup();
        currentMode = LightModes::JustLight;
        break;
        
      case 0xFF30CF:
        Serial.println(F("Pressed 1: Twinkle fox"));
        twinkleFoxSetup();
        currentMode = LightModes::TwinkleFox;
        break;
        
      case 0xFF18E7:
        Serial.println(F("Pressed 2: Pacifica"));
        pacificaSetup();
        currentMode = LightModes::Pacifica;
        break;
        
      case 0xFF7A85:
        Serial.println(F("Pressed 3: Pride2015"));
        pride2015Setup();
        currentMode = LightModes::Pride2015;
        break;
        
      case 0xFF10EF:
        Serial.println(F("Pressed 4: First light"));
        // firstLightSetup();
        currentMode = LightModes::FirstLight;
        break;
        
      case 0xFF38C7:
        Serial.println(F("Pressed 5: Blink"));
        // blinkSetup();
        currentMode = LightModes::Blink;
        break;

      case 0xFF5AA5:
        Serial.println(F("Pressed 6: Color temperature"));
        // colorTemperatureSetup();
        currentMode = LightModes::ColorTemperature;
        break;

      case 0xFF42BD:
        Serial.println(F("Pressed 7: Demo reel 100"));
        // demoReel100Setup();
        currentMode = LightModes::DemoReel100;
        break;

      case 0xFF4AB5:
        Serial.println(F("Pressed 8: Just blue"));
        justBlueSetup();
        currentMode = LightModes::JustBlue;
        break;

      case 0xFF52AD:
        Serial.println(F("Pressed 9: Just green"));
        justGreenSetup();
        currentMode = LightModes::JustGreen;
        break;
  }
}
