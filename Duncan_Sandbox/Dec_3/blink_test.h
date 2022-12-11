/* SDSMT
 * #11ModularGameController
 * written by Duncan McGonagle
 * libraries used Adafruit Seesaw
 * This example shows how to blink a pin on a seesaw.
 * It is written to use the built-in LED on the ATtiny817 breakout with seesaw.
 * Future Iteration: Use this code as a base to intialize individual pins
 */
 
#ifndef BLINK_TEST_H
#define BLINK_TEST_H


#include "globals.h"
#include "Adafruit_seesaw.h"

//functions
void blink_setup(int i2c_addresses[]);
void blink_tests() ;



//pin on the seesaw devices that control the LED
#define BLINK_PIN 5

//seesaw modules to be initialized
Adafruit_seesaw module[8];




/* blink_setup recieves an array of addresses
*  These addresses come from i2c_scan.h
*/
void blink_setup(int i2c_addresses[]) {

for (int i = 0; i < nDevices; i++)
{
  if(!module[i].begin(i2c_addresses[i]))
  {
    Serial.print(nDevices);
    Serial.println(" :seesaw not found!");
    delay(10);
  }
}
  
Serial.println(F("seesaw devices started OK!"));

//sets the pinmode for each connected module
for (int i = 0; i < nDevices; i++)
{
  module[i].pinMode(BLINK_PIN, OUTPUT);
  module[i].digitalWrite(BLINK_PIN, HIGH);   // turn the LED on (the LED is tied low)
}

}




/* blink_tests writes to the modules sequentially
*  since the devices have already been set up
*  it only needs to send the digitalWrite function to 
*  each module
*/
void blink_tests() 
{
     
  for (int i = 0; i < nDevices; i++)
  {
  module[i].digitalWrite(BLINK_PIN, LOW);   // turn the LED on (the LED is tied low)
  Serial.print("Module ");
  Serial.print(i + 1);
  Serial.print(", address 0x");
  Serial.print(i2c_addresses[i],HEX);
  Serial.println(" turned on!");
 
  delay(1000);// wait for a second
  
  module[i].digitalWrite(BLINK_PIN, HIGH);    // turn the LED off
  }
  delay(500); 

}

#endif