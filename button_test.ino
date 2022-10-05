//SDSMT
//#11ModularGameController
//written by Duncan McGonagle
//libraries used BleKeyboard
//code references exmamples used in the BleKeyboard.h BLEMouse.h and Keyboard.h libraries
//Bugs: Mouse is not working

#include <BleConnectionStatus.h>
#include <BleKeyboard.h>
//#include <BleMouse.h>

BleKeyboard bleKeyboard;

//BleMouse bleMouse;




//sets up bluetooth and inputs
void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  //bleMouse.begin();
  
  // make pin 2 - 5 are set as inputs
  //Input is high until it is 
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

}


//The esp32 is connected to 4 buttons
//each button corresponds to a single keyboard press
void loop() {

  //checks to see if the ESP32 is connected over bluetooth
  //if the esp32 is on but is not connected to a pc it won't send 
  //keystrokes
  if(bleKeyboard.isConnected() ) {

    if (digitalRead(2) == LOW) 
    {
    Serial.println("Sending 'A press'...");
    bleKeyboard.print("A");
    }

    if (digitalRead(3) == LOW) 
    {
     Serial.println("Sending 'S press'...");
    bleKeyboard.print("S");
    }
    
     if (digitalRead(4) == LOW) 
    {
     Serial.println("Sending 'D press'...");
    bleKeyboard.print("D");
    }
    
     if (digitalRead(5) == LOW) 
    {
     Serial.println("Sending 'F press'...");
    bleKeyboard.print("F");
    }

    //small delay between inputs
    delay(10);
    
    //checks to see if mouse is connected
    /*if(bleMouse.isConnected()) {
    Serial.println("Scroll Down");
    bleMouse.move(25,25,0);
  }
    */
    
  }
}
