/*
 * This example shows how to blink a pin on a seesaw.
 * It is written to use the built-in LED on the ATtiny817 breakout with seesaw.
 */

#include "globals.h"
#include "Adafruit_seesaw.h"


#define BLINK_PIN 5

Adafruit_seesaw module[8];

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

for (int i = 0; i < nDevices; i++)
{
  module[i].pinMode(BLINK_PIN, OUTPUT);
  module[i].digitalWrite(BLINK_PIN, HIGH);   // turn the LED on (the LED is tied low)
  
}

}

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
