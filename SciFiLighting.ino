#include<IRremote.h>
#include "FastLED.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Packer.h>
#include <ArduinoJson.h>

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

//#define FASTLED_ALLOW_INTERRUPTS 0

#define LISTEN_RADIO        true
#define NUM_LEDS            6 //Quantity of leds
#define LED_TYPE            WS2811
#define COLOR_ORDER         GRB
#define DATA_PIN            9
#define VOLTS               5
#define MAX_POWER_MILLIAMPS 500
#define BrightnessRate      51 //How many to increase/decrease brightness if corresponding button was pressed

void messageReceiveHandler(char arr[], int size);

CRGB                        globalLedsArr[NUM_LEDS]; // Define the array of leds which will be used by all other algorithms

Packer                      packer;
RF24                        radio(7, 8); // CE, CSN
const byte address[6] =     "00001";

String currentMode =        "TurnOff"; //Is used to define which algorithm to use for scifi backlight, depending on it we use specific algorithm
const int delayPeriod =     100; //This is used in special sleep functions with build in listener(swiches command if new signal was received)
int BRIGHTNESS =            255; //Used by all light modes.

int recv_pin =              2;
IRrecv                      receiver(recv_pin);
decode_results              results;

void setup()
{
  //Disable light if it was enabled
  turnOffSetup();
  turnOffLoop();

  // It's important to set the color correction for your LED strip here,
  // so that colors can be more accurately rendered through the 'temperature' profiles
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(globalLedsArr, NUM_LEDS).setCorrection( TypicalSMD5050 );
 
  // 3 second delay for boot recovery, and a moment of silence
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay( 1000 ); // power-up safety delay

  turnOnBacklight();
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  receiver.enableIRIn();

  packer.onMessageReady(messageReceiveHandler);
  packer.setDebug(false);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  StaticJsonDocument<64> doc;

  char arr[] = "{\"command\":1234}";

  deserializeJson(doc, arr);
  // JsonObject obj = doc.as<JsonObject>();
  Serial.print(F("\nResult: "));
  int test = doc["command"];
  Serial.println(test);
  serializeJson(doc, Serial);

  delay(1000);

  sleep(0); //Run method which have to work in paralel with other programs
  listenRF(); //Temporarly, listen here
  
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
    Serial.print(F("HEX command value: "));
    Serial.println(results.value, HEX);
    receiver.resume(); //Continue receiving
    
    mapper(results.value);//Call mapper to perform operation
    
    newCommand = true;
  }
  
  return newCommand;
}

/* Listen IR if there is a command. true if new command detected */
bool listenRF() {
  bool newCommandReceived = false;
  if(!LISTEN_RADIO) return false;
  // Serial.println((String) F("Free: ") + freeRAM());

  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    builtPack built = packer.getBuiltPack(text, sizeof(text));
    // packer.printPack(built);
    packer.pushPack(packer.restorePack(built));
    newCommandReceived = true; //Not always
  }
  // Serial.println(F("Listening ..."));
  // delay(5);
  
  return newCommandReceived;
}

/*Handler called when package was received via RF communication*/
void messageReceiveHandler(char arr[], int size) {
  Serial.print(F("Received message: "));
  for(int i = 0; i < size; i++) {
    Serial.print(arr[i]);
  }

  DynamicJsonDocument doc(256);

  deserializeJson(doc, arr, size);
  JsonObject obj = doc.as<JsonObject>();
  Serial.print(F("\nResult: "));
  float test = obj["command"];
  Serial.println(test);
  serializeJson(doc, Serial);
  // Serial.println(obj.containsKey("command"));
  // Serial.print(F("HEX command value: "));
  // Serial.println(results.value, HEX);
  // mapper(results.value);//Call mapper to perform operation
  // Serial.println();
}

int freeRAM() {
  int value = 0;
  int result = 0;
  extern int *__brkval;
  extern int __heap_start;
  result = (int)&value - ((int)__brkval == 0 ? (int)&__heap_start : (int)__brkval);
  return result;
}
