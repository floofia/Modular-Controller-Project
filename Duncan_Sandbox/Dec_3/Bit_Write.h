#include "globals.h"
//#include "i2c_scan.h"

int string_convert_int();
String string_read();
void all_devices_output();
void all_devices_buffer();
void read_entire_rom(Adafruit_seesaw ss);
void read_device_rom(Adafruit_seesaw ss);
void write_device_rom_sequence(Adafruit_seesaw &ss);
void write_device_address(Adafruit_seesaw &ss);
void write_device_mod_name(Adafruit_seesaw ss);
void write_device_dev_type(Adafruit_seesaw ss);
String mod_type(int type);

Adafruit_seesaw ss;
Adafruit_seesaw i2c_outputs[8];


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

  i2c_scan();
  i2c_scan();

  Serial.println("START");

  
  for (int i = 0; i < nDevices; i++)
  {
    if (!i2c_outputs[i].begin(i2c_addresses[i]))
    {
      //Serial.print(nDevices);
      Serial.println("Address 0000, BAD, BAD, BAD");
      //delay(10);
    }

    read_device_rom(i2c_outputs[i]);

  }
  
  Serial.println("END");
  Serial.println();

}



void all_devices_buffer()
{

  i2c_scan();
  i2c_scan();

 for (int i = 0; i < nDevices; i++)
  {
    if (!i2c_outputs[i].begin(i2c_addresses[i]))
    {
      //Serial.print(nDevices);
     // Serial.println("Address 0000, BAD, BAD, BAD");
      //delay(10);
    }

   // read_device_rom(i2c_outputs[i]);

  }
  


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
  Serial.print(", ");
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


void write_device_rom_sequence(Adafruit_seesaw &ss)
{

  write_device_mod_name(ss);

  write_device_dev_type(ss);

  write_device_address(ss);


  ss.begin();
}

void write_device_address(Adafruit_seesaw &ss)
{
  int address = 50;
  int eepromval = 0;

  Serial.print(F("Initial Device Address: "));
  address = ss.EEPROMRead8(127);
  Serial.print(address);
  Serial.println();
  Serial.println();
  Serial.print(F("Enter new Device Address [[between 25 and 125]]: "));

  eepromval = string_convert_int();

  if (!(eepromval > 25 && eepromval < 125))
  {
    while (!(eepromval > 25 && eepromval < 125))
    {
    Serial.println();
    Serial.println();
    Serial.print("Enter a value between 25 and 125: ");
    eepromval = string_convert_int();
    
    }

  }

  ss.EEPROMWrite8(127, eepromval);

  ss.begin(eepromval);
 // Serial.print(F("New Device Address: "));
 // address = ss.EEPROMRead8(127);
  //Serial.print(address);
  Serial.println();
  Serial.println();
  Serial.println();

}


void write_device_mod_name(Adafruit_seesaw ss)
{
  String string;
  char module_name[32];
  int eepromval;
  int i;

  Serial.print("Initial Name of Device: ");
  for (i = 0; i < 32; i++)
  {
    eepromval = ss.EEPROMRead8(i);
    module_name[i] = (char)eepromval;
  }

  Serial.println(module_name);
  Serial.println();

  Serial.print("Enter New Name for Device: ");
  string = string_read();
  Serial.println();
  string.toCharArray(module_name, 32);

  Serial.println();
  Serial.println("!!Writing Name!!");
  for (i = 0; i < 32; i++)
  {
    ss.EEPROMWrite8(i, module_name[i]);
  }
  Serial.println();
  Serial.print("New Name of Device: ");
  for (i = 0; i < 32; i++)
  {
    eepromval = ss.EEPROMRead8(i);
    module_name[i] = (char)eepromval;
  }


  Serial.print(module_name);
  Serial.println();
  Serial.println();
  Serial.println();

}

void write_device_dev_type(Adafruit_seesaw ss)
{
 
  
  int device_type;
  int eepromval;
  int address;

  Serial.print("Initial Device Type: ");
  device_type = ss.EEPROMRead8(126);
  Serial.print(device_type);
  Serial.println();
  Serial.println();
  
  Serial.println("Device Types: ");
  
  for (int i = 0; i < 13; i++){Serial.println(names_dev[i]);}

  Serial.print("Enter New Device Types: ");

  
  eepromval = string_convert_int();
  Serial.println();
  ss.EEPROMWrite8(126, eepromval);
  //Serial.print("New Device Type: ");
  //address = ss.EEPROMRead8(126);
  Serial.println();
  //Serial.print(address);

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
