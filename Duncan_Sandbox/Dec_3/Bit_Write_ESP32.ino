//write to aatiny817
//change bit in register
/*
   Read and Write values to the
*/
#include "globals.h"
#include "Adafruit_seesaw.h"
#include "serial_setup.h"
#include "i2c_scan.h"
#include "Bit_Write.h"


void setup() {
  uint8_t eepromval;
  uint8_t attiny_device;
  uint8_t device_register;
  int selection;

  serial_setup(115200);

  while (!Serial) delay(1000);   // wait until serial port is opened

  while (1)
  {

    
   /* for (int i = 0; i < 5; i++) {
      i2c_addresses[i] = 0;
    }

    i2c_scan();
    */

    i2c_scan();
    
    ss.begin(i2c_addresses[0]);

    i2c_scan();
    
    all_devices_buffer();
    all_devices_output();
    

    do
    {

      Serial.print("Enter Value of the i2c device you'd like to edit: ");
      attiny_device = string_convert_int();

      //Serial.println(attiny_device);
      Serial.println();
      Serial.println();

      if (!ss.begin(attiny_device))
      {
        Serial.println(F("seesaw failed to start"));
        Serial.println();
        all_devices_output();
      }


    } while (!ss.begin(attiny_device));

    do {
      selection = 0;
      Serial.println("READ MODULE       [1]");
      Serial.println("Write MODULE      [2]");
      Serial.println("READ ALL MODULES  [3]");
      Serial.println();
      Serial.print("Selection: ");
      selection = string_convert_int();
      Serial.println();
      Serial.println();
      
    } while ((selection != 1) && (selection != 2) && (selection != 3));

    switch (selection) {
      case 1:
        //read_entire_rom(ss);
        read_device_rom(ss);
        Serial.println();
        break;
      case 2:
        write_device_rom_sequence(ss);
        break;
      case 3:
        //all_devices_output();
        break;
      default:
        Serial.print("You shouldn't be here");
        break;
    }

  }
  i2c_scan();
  delay(1000);

}





void loop()
{
  //DONT WRITE EEPROM IN A LOOP!!!! YOU WILL DESTROY YOUR FLASH!!!
}
