/*
 * This function chses mode based on a pressed button, it also launches corresponding setup method 
 * 
 * 
*/
void mapper(long long int code) {
  switch(code) {
      case 0xFFA857:
        Serial.println("Pressed Plus: Increase brightness");
        increaseBrightness();
        break;

      case 0xFFE01F:
        Serial.println("Pressed Minus: Decrease brightness");
        decreaseBrightness();
        break;

        
      case 0xFFC23D:
        Serial.println("Pressed Play/Pause: TurnOff");
        turnOffSetup();
        currentMode = "TurnOff";
        break;
    
      case 0xFF6897:
        Serial.println("Pressed 0: Just light");
        justLightSetup();
        currentMode = "JustLight";
        break;
        
      case 0xFF30CF:
        Serial.println("Pressed 1: Twinkle fox");
//        updateLight();
        twinkleFoxSetup();
        currentMode = "twinkleFox";
        break;
        
      case 0xFF18E7:
        Serial.println("Pressed 2: Pacifica");
//        updateLight();
        pacificaSetup();
        currentMode = "Pacifica";
        break;
        
      case 0xFF7A85:
        Serial.println("Pressed 3: Pride2015");\
//        updateLight();
        pride2015Setup();
        currentMode = "Pride2015";
        break;
        
      case 0xFF10EF:
        Serial.println("Pressed 4: First light");
//        updateLight();
        firstLightSetup();
        currentMode = "FirstLight";
        break;
        
      case 0xFF38C7:
        Serial.println("Pressed 5: Blink");
//        updateLight();
        blinkSetup();
        currentMode = "Blink";
        break;

      case 0xFF5AA5:
        Serial.println("Pressed 6: Color temperature");
//        updateLight();
        colorTemperatureSetup();
        currentMode = "ColorTemperature";
        break;

      case 0xFF42BD:
        Serial.println("Pressed 7: Demo reel 100");
//        updateLight();
        demoReel100Setup();
        currentMode = "DemoReel100";
        break;

      case 0xFF4AB5:
        Serial.println("Pressed 8: Just blue");
        justBlueSetup();
        currentMode = "JustBlue";
        break;

      case 0xFF52AD:
        Serial.println("Pressed 9: Just green");
        justGreenSetup();
        currentMode = "JustGreen";
        break;
  }
}

//void updateLight() {
//  turnOffSetup();
//  currentMode = "TurnOff";
//  runModeAlgorithm(); //Manualy trigger algorithm
//  delay(3000);
//}
