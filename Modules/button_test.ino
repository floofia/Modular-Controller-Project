//SDSMT
//#11ModularGameController
//written by Duncan McGonagle
//libraries used BleKeyboard
//code references exmamples used in the BleKeyboard.h BLEMouse.h and Keyboard.h libraries
//https://github.com/T-vK/ESP32-BLE-Keyboard https://github.com/T-vK/ESP32-BLE-Mouse
//a repository that combines the two has been used instead
//https://github.com/blackketter/ESP32-BLE-Combo
//next iteration: merge the gamepad into the BLE combo library
//bugs: joystick needs more tuning, mouse will stray to the bottom right

#include <BleCombo.h>


// set pin numbers for switch, joystick axes, and LED:
const int switchPin = 0;      // switch to turn on and off mouse control
const int xAxis = 25;         // joystick X axis
const int yAxis = 26;         // joystick Y axis
const int ledPin = 5;         // Mouse control LED
// pins for reading button input
const int button1 = 2;        // type letter A
const int button2 = 3;        // type letter S
const int button3 = 4;        // type letter D
const int button4 = 5;        // type letter F

// parameters for reading the joystick:
int range = 128;               // output range of X or Y movement
int responseDelay = 5;         // response delay of the mouse, in ms
int threshold = range / 4;     // resting threshold
int center = 0;                // resting position value

bool mouseIsActive = false;    // whether or not to control the mouse
int lastSwitchState = LOW;        // previous switch state


//sets up bluetooth and inputs
void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  Keyboard.begin();
  Mouse.begin();
  
  // make pin 0, 2 - 5 are set as inputs
  //Input is high until it is 
  pinMode(switchPin, INPUT_PULLUP);       //the switch pin
  pinMode(button1, INPUT_PULLUP);         //tactile buttons
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);

}


//The esp32 is connected to 4 buttons and a joystick
//each button corresponds to a single keyboard press

void loop() {

  //checks to see if the ESP32 is connected over bluetooth
  //if the esp32 is on but is not connected to a pc it won't send 
  //keystrokes
  if(Keyboard.isConnected() ) {

    if (digitalRead(2) == LOW) 
    {
    Serial.println("Sending 'A press'...");
    Keyboard.print("A");
    }

    if (digitalRead(3) == LOW) 
    {
     Serial.println("Sending 'S press'...");
    Keyboard.print("S");
    }
    
     if (digitalRead(4) == LOW) 
    {
     Serial.println("Sending 'D press'...");
    Keyboard.print("D");
    }
    
     if (digitalRead(5) == LOW) 
    {
     Serial.println("Sending 'F press'...");
     Keyboard.print("F");
    }

  // read the joystick switch:
  int switchState = digitalRead(switchPin);
  // if it's changed and it's high, toggle the mouse state:
  if (switchState != lastSwitchState) {
    if (switchState == HIGH) {
      mouseIsActive = !mouseIsActive;
      // turn on LED to indicate mouse state:
      digitalWrite(ledPin, mouseIsActive);
    }
  }
  // save switch state for next comparison:
  lastSwitchState = switchState;

  // read and scale the two axes:
  int xReading = readAxis(25);
  int yReading = readAxis(26);

  // if the mouse control state is active, move the mouse:
  if (mouseIsActive) {
    Mouse.move(xReading, yReading, 0);
  }

  delay(responseDelay);
}

}

//From the Arduino website https://www.arduino.cc/reference/en/language/functions/usb/mouse/mousemove/
/*
  reads an axis (0 or 1 for x or y) and scales the analog input range to a range
  from 0 to <range>
*/
int readAxis(int thisAxis) {
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the rest position threshold, use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
  }

  // return the distance for this axis:
  return distance;

  }
  