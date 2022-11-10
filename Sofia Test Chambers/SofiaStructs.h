

//in theory we can assin a pin's output to each of these
//e.g. joystick (&pin3, &pin4, 0);

struct joystick
{
   signed char x,y;
   bool button;
};

struct buttons
{
   bool a, b, x, y, select, start, up, down, left, right, home, L, R, ZL, zR; 
};

struct trigger
{
   bool zL, zR, L, R;
};

struct Dpad
{
   bool up, down, left, right, hardLeft, hardRight, hardUp, hardDown;
};

struct audio
{
   signed char L_audio, R_audio;

};

struct rumble
{
   signed char L_rumble, R_rumble;

};




struct EEPROM
{
   char name[64];
   char tbd[60];
   char pins[2];
   char deviceType;
   char address; 
};