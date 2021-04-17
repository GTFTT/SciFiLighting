#include<IRremote.h>
#include "FastLED.h"

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

//#define FASTLED_ALLOW_INTERRUPTS 0

#define NUM_LEDS            6 //Quantity of leds
#define LED_TYPE            WS2811
#define COLOR_ORDER         GRB
#define DATA_PIN            9
#define VOLTS               5
#define MAX_POWER_MILLIAMPS 500
#define BrightnessRate      51 //How many to increase/decrease brightness if corresponding button was pressed

String currentMode = "TurnOff"; //Is used to define which algorithm to use for scifi backlight, depending on it we use specific algorithm
const int delayPeriod = 100; //This is used in special sleep functions with build in listener(swiches command if new signal was received)
int BRIGHTNESS = 255; //Used by all light modes.

int recv_pin = 2;
IRrecv receiver(recv_pin);
decode_results results;

void setup()
{
  //Disable light if it was enabled
  turnOffSetup();
  turnOffLoop();
 
  // 3 second delay for boot recovery, and a moment of silence
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay( 1000 ); // power-up safety delay

  turnOnBacklight();
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  receiver.enableIRIn();
}

void loop()
{

  sleep(0);
  
   runModeAlgorithm(); //Run currntly working algorithm(run loop method of currently working algorithm)
}

void turnOnBacklight() {
  currentMode = "JustLight";
  justLightSetup();
}

void increaseBrightness() {
  BRIGHTNESS += BrightnessRate;
  if(BRIGHTNESS > 255) BRIGHTNESS = 255;
  FastLED.setBrightness(BRIGHTNESS); //Set brightness whereever we are
}

void decreaseBrightness() {
  BRIGHTNESS -= BrightnessRate;
  if(BRIGHTNESS < 0) BRIGHTNESS = 0;
  FastLED.setBrightness(BRIGHTNESS); //Set brightness whereever we are
}

/*
 * Custo delay function, use this instead delay, becaue it can listen IR signals while delaying;
 * Returns bool value which indicates: Does sleeping was iterupted due to new commad received?
*/
bool sleep(int sleepTime) {
  int countOfPeriods = sleepTime / delayPeriod;
  int remainder = sleepTime % delayPeriod;

  int i = 0;
  bool receivedNewCommand = false;
  //Iterate each loop with period of 100 ms, if new comand received, change current command
  do {
    receivedNewCommand = listenIR();
    if(receivedNewCommand) break;
    delay(delayPeriod);//Delay for one period
    i++;
  } while(i < countOfPeriods);
  
  if(receivedNewCommand) {
    return true;
  } else {
//    delay(remainder); //Delay for remaining miliseconds
    return false;
  }
}

/*
 * Listen IR sensor for new commands and call mapper function if new commad was received.
 * Returns bool value which says: Was new command received?
*/
bool listenIR() {
  bool newCommand = false;
 
  // ********  added &results (a place to store the key code)
  if (receiver.decode(&results)){
    Serial.print("HEX command value: ");
    Serial.println(results.value, HEX);
    receiver.resume(); //Continue receiving
    
    mapper(results.value);//Call mapper to perform operation
    
    newCommand = true;
  }
  
  return newCommand;
}
