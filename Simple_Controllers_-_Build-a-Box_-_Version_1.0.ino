
#include "Nintendo.h"
/* This code uses the Nicohood Library
 * Use this code at your own risk
 * Code written by Simple Controllers and this code is open source.
 * Meaning its free to share, improve on, or anything you like!
 * Just remember to mention you used my code!
 * Version 2.0 I just suck at github
 */
//This makes the controller bidirection data line on pin number8
CGamecubeConsole GamecubeConsole(8);      //Defines a "Gamecube Console" sending data to the console on pin 8
Gamecube_Data_t d = defaultGamecubeData;   //Structure for data to be sent to console

//This is needed but you don't need a controller on pin 7
CGamecubeController GamecubeController1(7);

// Ints that will change when the SWITCH push button is pushed and increases a counter for profile switching.
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button




//This is the pinout of the controller.  Can be changed to your liking.  I may have mixed up some of the tilt pins but you can change that physically in your build or through the code.  Just do test runs along the way.
const int A = 22;
const int B = 24;
const int X = 26;
const int Y = 30;
const int Z = 35;
const int START = 31;

 int R = 34; // This is not a const int anymore because it needs to be overwitten for profile switching.
 int L = 36;
 int RLIGHT = 28; // This is not a const int anymore because it needs to be overwitten for profile switching.
//This is the value of analog shielding 74 is lightest possible on gamecube.  It varies from gamecube to dolphin no idea why.
 int RLIGHTv = 74; // This is not a const int anymore because it needs to be overwitten for profile switching.

int LLIGHT = 28;
int LLIGHTv = 74;


const int LEFT = 38;
const int RIGHT = 39;
const int UP = 40;
const int DOWN = 41;

//NEW!! Fixed the mixup of X1 and X2 buttons, they now correspond to the correct buttons.  
//If you are updating from 1.0/1.1 you might have to change the internal pins on your box or just swap the pin numbers here.
const int X1 = 44;
const int X2 = 45;
const int Y1 = 46;
const int Y2 = 47;

//This is analog tilt modifiers and can be changed to your liking
const int X1v = 27;
const int X2v = 55;
const int X3v = 73;

      int Y1v = 27; // This is not a const int anymore because it needs to be overwitten for profile switching.
      int Y2v = 53; // This is not a const int anymore because it needs to be overwitten for profile switching.
const int Y3v = 74;

const int CLEFT = 48;
const int CRIGHT = 49;
const int CUP = 50;
const int CDOWN = 51;

//THIS IS THE SWITCH/BUTTON TO TOGGLE MODIFIERS (X1, X2, Y1, Y2) TO DPAD
const int SWITCH = 12;

void setup()
{
  //This is establishing the pin assignments up there to input pins
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(X, INPUT_PULLUP);
  pinMode(Y, INPUT_PULLUP);
  pinMode(Z, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
  
  pinMode(R, INPUT_PULLUP);
  pinMode(L, INPUT_PULLUP);
  pinMode(RLIGHT, INPUT_PULLUP);
  pinMode(LLIGHT, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  
  pinMode(X1, INPUT_PULLUP);
  pinMode(X2, INPUT_PULLUP);
  pinMode(Y1, INPUT_PULLUP);
  pinMode(Y2, INPUT_PULLUP);
  
  pinMode(CLEFT, INPUT_PULLUP);
  pinMode(CRIGHT, INPUT_PULLUP);
  pinMode(CUP, INPUT_PULLUP);
  pinMode(CDOWN, INPUT_PULLUP);

  pinMode(SWITCH, INPUT_PULLUP);

  //This is needed to run the code.
  GamecubeController1.read();

 
}

void loop()
{
  //This resets and establishes all the values after the controller sends them to the console and helps with initial "zeroing"
  int pinA = 0;
  int pinB = 0;
  int pinX = 0;
  int pinY = 0;
  int pinZ = 0;
  int pinSTART = 0;

  int pinR = 0;
  int pinL = 0;
  int pinRLIGHT = 0;
  int pinLLIGHT = 0;

  int pinLEFT = 0;
  int pinRIGHT = 0;
  int pinUP = 0;
  int pinDOWN = 0;

  int pinX1 = 0;
  int pinX2 = 0;
  int pinY1 = 0;
  int pinY2 = 0;

  int pinCLEFT = 0;
  int pinCRIGHT = 0;
  int pinCUP = 0;
  int pinCDOWN = 0;

  int pinxAxisC = 128;
  int pinyAxisC = 128;
  
  int pinxAxis = 128;
  int xmod = 0;
  int pinyAxis = 128;

  int rightOne = 0;
  int leftOne = 0;
  int downOne = 0;

  int pinSWITCH = 0;

  //This reads control stick as neutral when both left/right or up/down is pressed at the same time.  Also sets parameters for the diffrent analog tilt modifiers IE: X1+X2 = X3
  //UPDATE: NOW CORRESPONDS TO PROPER SMASHBOX ANGLES
  if (digitalRead(LEFT) == HIGH && digitalRead(RIGHT) == LOW){
    pinxAxis = 128+86;
    if (digitalRead(X1) == LOW && digitalRead(X2) == HIGH)pinxAxis = X1v + 128;
    if (digitalRead(X1) == HIGH && digitalRead(X2) == LOW)pinxAxis = X2v + 128;
    if (digitalRead(X1) == LOW && digitalRead(X2) == LOW)pinxAxis = X3v + 128;
    rightOne = 1;
  }
  if (digitalRead(LEFT) == LOW && digitalRead(RIGHT) == HIGH){
    pinxAxis = 128-86;
    if (digitalRead(X1) == LOW && digitalRead(X2) == HIGH)pinxAxis = 128 - X1v;
    if (digitalRead(X1) == HIGH && digitalRead(X2) == LOW)pinxAxis = 128 - X2v;
    if (digitalRead(X1) == LOW && digitalRead(X2) == LOW)pinxAxis = 128 - X3v;
    leftOne = 1;
  }
    
  if (digitalRead(DOWN) == HIGH && digitalRead(UP) == LOW){
    pinyAxis = 128+86;
    if (digitalRead(Y1) == LOW && digitalRead(Y2) == HIGH)pinyAxis = 128 + Y1v;
    if (digitalRead(Y1) == HIGH && digitalRead(Y2) == LOW)pinyAxis = 128 + Y2v;
    if (digitalRead(Y1) == LOW && digitalRead(Y2) == LOW)pinyAxis = 128 + Y3v;
  }
  if (digitalRead(DOWN) == LOW && digitalRead(UP) == HIGH){
    pinyAxis = 128-86;
    if (digitalRead(Y1) == LOW && digitalRead(Y2) == HIGH)pinyAxis = 128 - Y1v;
    if (digitalRead(Y1) == HIGH && digitalRead(Y2) == LOW)pinyAxis = 128 - Y2v;
    if (digitalRead(Y1) == LOW && digitalRead(Y2) == LOW)pinyAxis = 128 - Y3v;
    downOne = 1;
  }

  //NEW: Axe Shield Drops
  if (digitalRead(X1) == HIGH && digitalRead(X2) == HIGH && digitalRead(Y1) == HIGH && digitalRead(Y2) == HIGH && downOne == 1 && leftOne == 1){
    pinxAxis = 128-80;
    pinyAxis = 128-78;
  }

  if (digitalRead(X1) == HIGH && digitalRead(X2) == HIGH && digitalRead(Y1) == HIGH && digitalRead(Y2) == HIGH && downOne == 1 && rightOne == 1){
    pinxAxis = 128+80;
    pinyAxis = 128-78;
  }

  //Reads CStick pins, same logic as controlstick values.
  if (digitalRead(CLEFT) == HIGH && digitalRead(CRIGHT) == LOW)pinxAxisC = 255;
  if (digitalRead(CLEFT) == LOW && digitalRead(CRIGHT) == HIGH)pinxAxisC = 0;
  if (digitalRead(CDOWN) == HIGH && digitalRead(CUP) == LOW)pinyAxisC = 255;
  if (digitalRead(CDOWN) == LOW && digitalRead(CUP) == HIGH)pinyAxisC = 0;

  if (digitalRead(A) == LOW)pinA = 1;
  
   
  if (digitalRead(B) == LOW)pinB = 1;
  
  if (digitalRead(X) == LOW)pinX = 1;
  if (digitalRead(Y) == LOW)pinY = 1;
  if (digitalRead(Z) == LOW)pinZ = 1;
  if (digitalRead(START) == LOW)pinSTART = 1;
    
  
  //This is for analog shield
  if (digitalRead(RLIGHT) == LOW)pinRLIGHT = RLIGHTv;
  if (digitalRead(LLIGHT) == LOW)pinLLIGHT = LLIGHTv;
  //This is for digital shield
  if (digitalRead(R) == LOW)pinR = 1;
  if (digitalRead(L) == LOW)pinL = 1;

  if (digitalRead(SWITCH) == LOW)pinSWITCH = 1;

  d.report.dup = 0;
  d.report.dright = 0;
  d.report.ddown = 0;
  d.report.dleft = 0;
    


// This code causes the values of Y1v, Y2v, RLIGHT, R, and RLIGHTv to switch based on a buttonstate counter.
// Essentially, if SWITCH is pushed, it increments buttonPushCounter by 1, and if it's a multiple of 3 it switches to
// Y1v and Y2v have appropriate angles for Project M shield drop and utilt. If it's a multiple of 4 it switches
// Y1v and Y2v for uptilt purposes in Smash Ult, then it switches R and RLIGHTs position on the pinout, because
// Smash ultimate cannot read hard press shield. Then, it sets RLIGHTv to 255, which is the hardest light shield press
// So you can get a normal shield. More profiles can be added by doing more multiples. 
 buttonState = digitalRead(SWITCH);

 if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
    } 
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;

  //This is the Project M profile I have set up.
  if (buttonPushCounter % 3 == 0) {
    
  Y2v = 70;
  Y1v = 53;
   //This is the smash Ultimate profile I have setup.
  } else if(buttonPushCounter % 4 == 0){
    
  Y2v = 70;
  Y1v = 43;
  RLIGHT = 34;
  R = 28;
  RLIGHTv = 255;
  LLIGHT = 36;
  L = 28;
  LLIGHTv = 255;

  }//This is the monster hunter / steam generic controller. It can't read the hard press and I have enabled to dpad since most modern games require it.
   else if(buttonPushCounter % 5 == 0){
    
  Y2v = 70;
  Y1v = 43;
  RLIGHT = 34;
  R = 28;
  RLIGHTv = 255;
  LLIGHT = 36;
  L = 28;
  LLIGHTv = 255;
  
   if(digitalRead(Y2) == LOW)d.report.dleft = 1;
    if(digitalRead(X2) == LOW)d.report.ddown = 1;
    if(digitalRead(Y1) == LOW)d.report.dup = 1;
    if(digitalRead(X1) == LOW)d.report.dright = 1;
  
    } else {
      //This is the melee profile, it is both the default and if you're on a mod that's not 3/4/5 then it'll be melee. 
      Y2v = 53;
      Y1v = 27;
      RLIGHT = 28;
      R = 34;
      RLIGHTv = 74;
      LLIGHT = 28;
      LLIGHTv = 74;
      L = 36;
      }
// These are commented out because it conflicts with how I have set up the profile switcher.
// Considering making the taunt button the light shield button and making modifier button cause light shield. 
// if (digitalRead(SWITCH) == LOW)pinSWITCH = 1;

//  d.report.dup = 0;
 // d.report.dright = 0;
 // d.report.ddown = 0;
 // d.report.dleft = 0;
    
  //NEW WHEN SWITCH/BUTTON ON PIN 12 IS PRESSED/ACTIVATED SWAPS X1,X2,Y1,Y2 TO DPAD 
  //if (pinSWITCH == 1){
  // if(digitalRead(X1) == LOW)d.report.dleft = 1;
   // if(digitalRead(X2) == LOW)d.report.ddown = 1;
    //if(digitalRead(Y1) == LOW)d.report.dup = 1;
   // if(digitalRead(Y2) == LOW)d.report.dright = 1;
 // }

  //reports data
  d.report.a = pinA;
  d.report.b = pinB;
  d.report.x = pinX;
  d.report.y = pinY;
  d.report.z = pinZ;
  d.report.start = pinSTART;
  d.report.r = pinR;
  d.report.l = pinL;
  d.report.left = pinRLIGHT;
  d.report.right = pinLLIGHT;
  d.report.xAxis = pinxAxis;
  d.report.yAxis = pinyAxis;
  d.report.cxAxis = pinxAxisC;
  d.report.cyAxis = pinyAxisC;
  //sends the complied data to console when console polls for the input
  GamecubeConsole.write(d);
}
