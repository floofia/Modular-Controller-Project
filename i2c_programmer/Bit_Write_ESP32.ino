//write to aatiny817
//change bit in register
/*
 * This example shows how to read and write EEPROM data. Try writing
 * then removing power from both devices, commenting out the write, and
 * uploading again.
 */
#include "globals.h"
#include "Adafruit_seesaw.h"
#include "serial_setup.h"
#include "i2c_scan.h"

Adafruit_seesaw ss;

void setup() {
  uint8_t eepromval;
  uint8_t attiny_device;
  uint8_t device_register;
  
  serial_setup(9600);
  
  while (!Serial) delay(100);   // wait until serial port is opened

while(1)
{
  i2c_scan();
  
{
  Serial.print("Enter Address of the i2c device in hex [0xFF for example]: ");
  attiny_device = Serial.read();
  
  if(!ss.begin(attiny_device)){
    Serial.println(F("seesaw not found!"));
     Serial.println(F("Enter appropriate address"));
 
  }
  
}while (!ss.begin(attiny_device));

  
  Serial.println(F("seesaw started OK!\n"));

  
  Serial.println(F("**PLEASE NOTE 0x7F register sets the address of the device!**"));
  Serial.print(F("Enter HEX of register to edit: "));
  device_register = Serial.read();
  
  Serial.print(F("\nInitial read from register: "));
  eepromval = ss.EEPROMRead8(device_register);
  Serial.println(eepromval, HEX);


  Serial.println(F("\nEnter new HEX value for the register: "));
  eepromval = Serial.read();
  ss.EEPROMWrite8(device_register, eepromval);

  Serial.print(F("\nSecond read from register "));
  Serial.println(ss.EEPROMRead8(device_register), HEX);
}

delay(1000);

}

void loop() {
  //DONT WRITE EEPROM IN A LOOP!!!! YOU WILL DESTROY YOUR FLASH!!!
}
