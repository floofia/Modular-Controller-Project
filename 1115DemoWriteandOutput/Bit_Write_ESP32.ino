//write to aatiny817
//change bit in register
/*
   Read and Write values to the
*/
#include "globals.h"
#include "Adafruit_seesaw.h"
#include "serial_setup.h"
#include "i2c_scan.h"

int string_convert_int();


Adafruit_seesaw ss;

Adafruit_seesaw i2c_outputs[8];

void setup() {
  uint8_t eepromval;
  uint8_t attiny_device;
  uint8_t device_register;
  int selection;

  serial_setup(57600);

  while (!Serial) delay(1000);   // wait until serial port is opened

  while (1)
  {
    for (int i = 0; i < 5; i++) {
      i2c_addresses[i] = 0;
    }

    i2c_scan();
    
    all_devices_output();


    do
    {

      Serial.print("Enter Value of the i2c device you'd like to edit: ");
      attiny_device = string_convert_int();

      Serial.println(attiny_device);

      if (!ss.begin(attiny_device))
      {
        Serial.println(F("seesaw failed to start"));
      }


    } while (!ss.begin(attiny_device));

    do {
      selection = 0;
      Serial.println("READ MODULE       [1]");
      Serial.println("Write MODULE      [2]");
      Serial.println("READ ALL MODULES  [3]");
      Serial.println();
      selection = string_convert_int();

    } while ((selection != 1) && (selection != 2) && (selection != 3));

    switch (selection) {
      case 1:
        //read_entire_rom(ss);
        read_device_rom(ss);
        break;
      case 2:
        write_device_rom_sequence(ss);
        break;
      case 3:
        all_devices_output();
        break;
      default:
        Serial.print("You shouldn't be here");
        break;
    }

  }

  delay(1000);

}





void loop()
{
  //DONT WRITE EEPROM IN A LOOP!!!! YOU WILL DESTROY YOUR FLASH!!!
}



int string_convert_int()
{
  String string;
  char char_array[32];
  int hex;

  while (Serial.available() == 0) {}

  string = Serial.readStringUntil('\0');

  //string.toCharArray(char_array, 32);

  return string.toInt();
  //hex = strtoul(char_array, NULL, 32);
  //return hex;

}


String string_read()
{

  String string;
  char char_array[32];
  int hex;

  while (Serial.available() == 0) {}

  string = Serial.readStringUntil('\0');

  //string.toCharArray(char_array, 32);

  // string.toCharArray(char_array, 64);

  return string;
  //hex = strtoul(char_array, NULL, 32);
  //return hex;

}


void all_devices_output()
{

  Serial.println("START");
  for (int i = 0; i < nDevices; i++)
  {
    if (!i2c_outputs[i].begin(i2c_addresses[i]))
    {
      Serial.print(nDevices);
      Serial.println(" :seesaw not found!");
      delay(10);
    }

    read_device_rom(i2c_outputs[i]);

  }
  Serial.println("END");
  Serial.println();

}


//read 0-127
void read_entire_rom(Adafruit_seesaw ss)
{
  int i;
  int eepromval;

  for (i = 0; i < 128; i++)
  {
    Serial.print(F("\nInitial read from register: "));
    eepromval = ss.EEPROMRead8(i);
    Serial.println(eepromval);
  }

}


void read_device_rom(Adafruit_seesaw ss)
{
  char module_name[64];
  int pin1, pin2;
  int device_type;
  int address, eepromval;
  String dev_type;
  int i;

  //Serial.print(F("\nName of Device: "));

  for (i = 0; i < 64; i++)
  {
    eepromval = ss.EEPROMRead8(i);
    module_name[i] = (char)eepromval;
  }

  //Serial.print(F("\nPins of Device Used: "));
  pin1 = ss.EEPROMRead8(124);
  pin2 = ss.EEPROMRead8(125);


  //Serial.print(F("\nDevice Type: "));
  device_type = ss.EEPROMRead8(126);

  if (device_type > 15) {
    dev_type = "Feedback";
  }
  if (device_type % 16 > 0) {
    dev_type = "Input";
  }
  if (device_type == 0) {
    dev_type = "Passive";
  }

  //Serial.print(F("\nAddress: "));
  address = ss.EEPROMRead8(127);

  //address

  Serial.print("Address ");
  Serial.print(address);
  Serial.print(": ");
  //module name
  Serial.print(module_name);
  Serial.print(", ");
  //device type
  Serial.print(dev_type);
  Serial.print(", ");
  //device
  Serial.print(mod_type(device_type));
  Serial.println();


}



void write_device_rom_sequence(Adafruit_seesaw ss)
{
  //write_device_address(ss);

  write_device_mod_name(ss);

  write_device_dev_type(ss);
}

void write_device_address(Adafruit_seesaw ss)
{
  int address;
  int eepromval;

  Serial.print(F("Initial Device Address: "));
  address = ss.EEPROMRead8(127);
  Serial.print(address);
  Serial.println();
  Serial.print(F("Enter new Device Address [[between 25 and 127]]: \n"));

  while(eepromval > 25 && eepromval < 127)
  {
  eepromval = string_convert_int();

  if (!(eepromval > 25 && eepromval < 128)){Serial.println("Enter a value between 25 and 127");
  }

  
  ss.EEPROMWrite8(127, eepromval);
  Serial.println(F("New Device Address: "));
  address = ss.EEPROMRead8(127);
  Serial.print(address);
  Serial.println();


}



void write_device_mod_name(Adafruit_seesaw ss)
{
  String string;
  char module_name[64];
  int eepromval;
  int i;

  Serial.print("Initial Name of Device: ");
  for (i = 0; i < 64; i++)
  {
    eepromval = ss.EEPROMRead8(i);
    module_name[i] = (char)eepromval;
  }

  Serial.println(module_name);


  Serial.println("Enter New Name for Device: ");
  string = string_read();
  string.toCharArray(module_name, 64);


  Serial.println(F("Writing Name:"));
  for (i = 0; i < 64; i++)
  {
    ss.EEPROMWrite8(i, module_name[i]);
  }

  Serial.print("New Name of Device: ");
  for (i = 0; i < 64; i++)
  {
    eepromval = ss.EEPROMRead8(i);
    module_name[i] = (char)eepromval;
  }

  Serial.println(module_name);
  Serial.println();

}

void write_device_dev_type(Adafruit_seesaw ss)
{
  int device_type;
  int eepromval;
  int address;

  Serial.println(F("Initial Device Type: "));
  device_type = ss.EEPROMRead8(126);
  Serial.print(device_type);
  Serial.println();
  Serial.println("Enter new Device Type: ");
  eepromval = string_convert_int();
  ss.EEPROMWrite8(126, eepromval);
  Serial.println("New Device Type: ");
  address = ss.EEPROMRead8(126);
  Serial.print(address);

}




String mod_type(int type)
{

  String dev_type;

  switch (type) {
    case 0b00000000:
      dev_type = "Passive";
      break;
    case 0b00010000:
      dev_type = "Audio";
      break;
    case 0b00100000:
      dev_type = "Visual Feedback";
      break;
    case 0b00110000:
      dev_type = "Haptic";
      break;
    case 0b00000001:
      dev_type = "D-Pad";
      break;
    case 0b00000010:
      dev_type = "Joystick";
      break;
    case 0b00000011:
      dev_type = "Button";
      break;
    case 0b00000100:
      dev_type = "Keyboard";
      break;
    case 0b00000101:
      dev_type = "Trigger";
      break;
    default:
      dev_type = "default";
      break;
  }

  return dev_type;


}
