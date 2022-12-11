#include "globals.h"
#include "serial_setup.h"
#include "i2c_scan.h"
#include "blink_test.h"

void setup() 
{
  serial_setup(9600);
  
}

void loop() 
{
  // put your main code here, to run repeatedly:
  i2c_scan();
  Serial.println("Devices Scanned!\n");
  
  blink_setup(i2c_addresses);
  Serial.println("Devices Setup!");

  blink_tests();
  Serial.println("Blink Test Complete\n");

}
