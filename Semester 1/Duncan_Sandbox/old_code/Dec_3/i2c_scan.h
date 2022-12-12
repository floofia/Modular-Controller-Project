/* SDSMT
*  Code Base by Nick Gammon
*  https://www.gammon.com.au/forum/?id=10896
*
* written/modified by Duncan McGonagle
*
* Detects the addresses of i2c devices connected to the esp-32
*
* Future Iteration: This is not how I want to handle detecting
* address, I will be modifying this code to use my own
* Implementaion to better fit the project
*/
#ifndef I2C_SCAN_H
#define I2C_SCAN_H


#include <Wire.h>
#include "globals.h"

//functions   
void i2c_scan_verbose();
void i2c_scan();

  
/* Detects the connected i2c devices and saves their addresses
*  to an array that can be used to initialize multiple
*  attiny917 seesaw devices, verbose is useful as it is nice for error checking
*  This function is not used in the program
*/
    void i2c_scan_verbose()
    {

      Wire.begin();

      //address and error check flag
      byte error, address;
      
      Serial.println();
      Serial.println("Scanning...");

    //initialize the addresses before having them set
     for (int i = 0; i < 5; i++) 
     {
      i2c_addresses[i] = 0;
     }
     
    //set device connected to 0 and incremented as they are detected
    nDevices = 0;

      
      for(address = 1; address < 127; address++ )
      {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        //with no errors deteceted the i2c address is returned
        //and saved into an array to intialize the attiny817s
        if (error == 0)
        {
          Serial.print("I2C device found at address: ");
          if (address<16)
            Serial.print("0");
          Serial.print(address);
          Serial.println("  !");
          i2c_addresses[nDevices] = address;
          nDevices++;
        }
        //if there was an error reading a device
        else if (error==4)
        {
          Serial.print("Unknown error at address 0x");
          if (address<16)
            Serial.print("0");
          Serial.println(address);
        }    
      }
      //if no devices are connected
      if (nDevices == 0){
        Serial.println("No I2C devices found\n");
      }
      else
      {
        Serial.print("Total Devices: ");
        Serial.println(nDevices);
        Serial.println("done");
        Serial.println();
      }
      
      delay(10);           // wait .1 seconds
    }


/* Near identical to i2c_scan_verbose however it only displays
*  an error if something goes wrong
*/
    void i2c_scan()
    {

      Wire.begin();
      
      //address and error check flag
      byte error, address;


    //initialize the addresses before having them set
     for (int i = 0; i < 5; i++) {i2c_addresses[i] = 0;}

     //set connected devices to 0 and increment as they are detected
     nDevices = 0;
 
      
      for(address = 1; address < 127; address++ )
      {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device is associated to an address
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        
        //save address to the global array
        if (error == 0)
        {
          i2c_addresses[nDevices] = address;
          nDevices++;
        }
           else
            {
               Serial.print("ERROR");
            }
       
        delay(10);           // wait .1 seconds
      }
    }

#endif