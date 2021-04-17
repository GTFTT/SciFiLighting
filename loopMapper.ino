/*
 * We have many algorithms here,to run specific one we just select its loop method based on global
 * mode variable
*/
void runModeAlgorithm() {

  if(currentMode == "twinkleFox") twinkleFoxLoop();
  if(currentMode == "Pacifica") pacificaLoop();
  if(currentMode == "Pride2015") pride2015Loop();
  if(currentMode == "FirstLight") firstLightLoop();
  if(currentMode == "Blink") blinkLoop();
  if(currentMode == "ColorTemperature") colorTemperatureLoop();
  if(currentMode == "DemoReel100") demoReel100Loop();
  if(currentMode == "JustLight") justLightLoop();
  if(currentMode == "TurnOff") turnOffLoop();
  if(currentMode == "JustBlue") justBlueLoop();
  if(currentMode == "JustGreen") justGreenLoop();
  
}
