#include <IRremote.h>
//Requires FastLED 3.1 or later; check github for latest code
#include <FastLED.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Packer.h>
#include <ArduinoJson.h>

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
// CRGBArray<NUM_LEDS>         globalLedsArr; //This is eqvivalent to previous one, but works for Twinkle fox
enum class LightModes {
  TurnOff,
  JustLight,
  JustBlue,
  JustGreen,
  Blink,
  FirstLight,
  DemoReel100,
  ColorTemperature,
  Pride2015,
  Pacifica,
  PartyMode
};

Packer                      packer;
RF24                        radio(7, 8); // CE, CSN
const byte address[6] =     "00001";
StaticJsonDocument<64>      doc; //Document for decoding data from rf messages

const int delayPeriod =     40; //This is used in special sleep functions with build in listener(swiches command if new signal was received)
int BRIGHTNESS =            255; //Used by all light modes.
LightModes currentMode =    LightModes::TurnOff; //Is used to define which algorithm to use for scifi backlight, depending on it we use specific algorithm

int recv_pin =              2;
IRrecv                      receiver(recv_pin);
decode_results              results;

void setup()
{
  // It's important to set the color correction for your LED strip here,
  // so that colors can be more accurately rendered through the 'temperature' profiles
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(globalLedsArr, NUM_LEDS).setCorrection( TypicalSMD5050 );

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
  listenRF();
  sleep(0); //Run method which have to work in paralel with other programs
  
  runModeAlgorithm(); //Run currntly working algorithm(run loop method of currently working algorithm)
}

void turnOnBacklight() {
  currentMode = LightModes::JustLight;
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

  int i = 0;
  bool receivedNewCommand = false;
  //Iterate each loop with period of 100 ms, if new comand received, change current command
  do {
    receivedNewCommand = listenIR();
    if(receivedNewCommand) break;
    delay(delayPeriod);//Delay for one period
    i++;
  } while(i < countOfPeriods);
  
  return receivedNewCommand;
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

/* Listen IR if there is a pack. When message will be generated, callback will be callde*/
bool listenRF() {
  if(!LISTEN_RADIO) return false;

  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    builtPack built = packer.getBuiltPack(text, sizeof(text));
    packer.pushPack(packer.restorePack(built));

    return true;
  }

  return false;
}

/*Handler called when message was received via RF communication*/
void messageReceiveHandler(char arr[], int size) {
  if(size > 40) {
    Serial.println(F("Message too big, aborting"));
    return;
  }
  
  deserializeJson(doc, arr, size);
  long code = doc["code"];
  Serial.print(F("Received code via RF:"));
  Serial.println(code);

  mapper(code);//Call mapper to perform operation
}
