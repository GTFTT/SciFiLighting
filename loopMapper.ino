/*
 * We have many algorithms here,to run specific one we just select its loop method based on global
 * mode variable
*/
void runModeAlgorithm() {

  // if(currentMode == LightModes::TwinkleFox) twinkleFoxLoop();
  if(currentMode == LightModes::MyMode) myModeLoop();
  if(currentMode == LightModes::Pacifica) pacificaLoop();
  if(currentMode == LightModes::Pride2015) pride2015Loop();
  if(currentMode == LightModes::FirstLight) firstLightLoop();
  if(currentMode == LightModes::Blink) blinkLoop();
  if(currentMode == LightModes::ColorTemperature) colorTemperatureLoop();
  if(currentMode == LightModes::DemoReel100) demoReel100Loop();
  if(currentMode == LightModes::JustLight) justLightLoop();
  if(currentMode == LightModes::TurnOff) turnOffLoop();
  if(currentMode == LightModes::JustBlue) justBlueLoop();
  if(currentMode == LightModes::JustGreen) justGreenLoop();
  
}
