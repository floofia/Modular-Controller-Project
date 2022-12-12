/* SDSMT
 * #11ModularGameController
 * written by Duncan McGonagle, Sofia Sadun
 * File with Global Variables to be used by multiple files
*/

#ifndef GLOBALS_H
#define GLOBALS_H

//addresses read from connectec attiny817 devices
extern int i2c_addresses[5] = {0, 0, 0, 0, 0};
//number of connected devices;
extern int nDevices = 0;

//menu for showing device type options
extern String names_dev[] = {"###################",
  "Passive -- 0", 
  "Audio -- 16",
  "Visual -- 32",
  "Haptic -- 48",
  "----------------",
  "D-Pad -- 1",
  "Joystick -- 2",
  "Keyboard -- 4",
  "Trigger -- 5",
  "###################"};


#endif
