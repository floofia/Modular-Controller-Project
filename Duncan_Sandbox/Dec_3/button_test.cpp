//SDSMT
//#11ModularGameController
//written by Duncan McGonagle
//libraries used BleCombo
//code references exmamples used in the BleKeyboard.h BLEMouse.h and Keyboard.h libraries
//https://github.com/T-vK/ESP32-BLE-Keyboard https://github.com/T-vK/ESP32-BLE-Mouse
//a repository that combines the two has been used instead
//https://github.com/blackketter/ESP32-BLE-Combo
//next iteration: merge the gamepad into the BLE combo library
//merge with Bit_Write_ESP32

#include <Arduino.h>
#include <BleCombo.h>
#include "Adafruit_seesaw.h"

// pins for reading button input
const int button1 = 0;        // type letter D
const int button2 = 1;        // type letter S
const int button3 = 2;        // type letter A
const int button4 = 3;        // type letter W


//seasaw device to be initialized
Adafruit_seesaw ss;


//sets up bluetooth and inputs
void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  Keyboard.begin();
  //Mouse.begin();

  //address of the seesaw device
  ss.begin(45);

  // make pin 0, 2 - 5 are set as inputs
  //Input is high until it is 
  ss.pinMode(button1, INPUT_PULLUP);         //tactile buttons
  ss.pinMode(button2, INPUT_PULLUP);
  ss.pinMode(button3, INPUT_PULLUP);
  ss.pinMode(button4, INPUT_PULLUP);

  ss.digitalWrite(button1, HIGH);            //initialize buttons
  ss.digitalWrite(button2, HIGH);
  ss.digitalWrite(button3, HIGH);
  ss.digitalWrite(button4, HIGH);

}


//The esp32 is connected to 4 buttons and a joystick
//each button corresponds to a single keyboard press
//update this 
void loop() {

  //checks to see if the ESP32 is connected over bluetooth
  //if the esp32 is on but is not connected to a pc it won't send 
  //keystrokes
  if(Keyboard.isConnected() ) {

    if (ss.digitalRead(button1) == LOW) 
    {
    Serial.println("Sending 'D press'...\n");
    Keyboard.print("D");
     Serial.println();
    }

    if (ss.digitalRead(button2) == LOW) 
    {
     Serial.println("Sending 'S press'...\n");
    Keyboard.print("S");
    
    }
    
     if (ss.digitalRead(button3) == LOW) 
    {
     Serial.println("Sending 'A press'...\n");
    Keyboard.print("A");
    Serial.println();
    }
    
     if (ss.digitalRead(button4) == LOW) 
    {
     Serial.println("Sending 'W press'...\n");
     Keyboard.print("W");
     Serial.println();
    }

  }

}




  
