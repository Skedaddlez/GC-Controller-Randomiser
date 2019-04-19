/*
  Copyright (c) 2014-2016 NicoHood
  See the readme for credit to other people.

  GamecubeConsole example
  Read controller and mirror data to the gamecube
*/

#include "Nintendo.h"

// Define a Gamecube Controller and a Console
CGamecubeController GamecubeController1(7);
CGamecubeConsole GamecubeConsole1(10);
Gamecube_Data_t d = defaultGamecubeData;

// Pin definitions
#define pinLed LED_BUILTIN

const int buttonPin = 2;
int buttonState = 0;


//Define arrays for randomiser
uint8_t digitalstates[12] = {};
long analogstates[6] = {};

//Define button IDs
int A = 0;
int B = 1;
int X = 2;
int Y = 3;
int START = 4;
int DL = 5;
int DR = 6;
int DU = 7;
int DD = 8;
int Z = 9;
int R = 10;
int L = 11;

int XA = 0;
int YA = 1;
int CX = 2;
int CY = 3;
int LEFT = 4;
int RIGHT = 5;


void setup()
{
  // Set up debug led
  pinMode(pinLed, OUTPUT);

  // Start debug serial
  Serial.begin(115200);

  //button as input
  pinMode(buttonPin, INPUT);
}


void loop()
{ 
  //Simple button for randomising
  buttonState=digitalRead(buttonPin);
  if (buttonState==HIGH){
    digitalWrite(pinLed, HIGH);
    randomise();
  }else{
    digitalWrite(pinLed, LOW);
    
   // Try to read the controller data
    if (GamecubeController1.read())
    {
      
      //get report
      auto r = GamecubeController1.getReport();

      //--------------------------------------

      //read and write analog states based on button IDs
      analogstates[0]=r.xAxis;
      d.report.xAxis=analogstates[XA];
      
      analogstates[1]=r.yAxis;
      d.report.yAxis=analogstates[YA];
      
      analogstates[2]=r.cxAxis;
      d.report.cxAxis=analogstates[CX];
      
      analogstates[3]=r.cyAxis;
      d.report.cyAxis=analogstates[CY];
  
      analogstates[4]=r.left;
      d.report.left=analogstates[LEFT];
      
      analogstates[5]=r.right;
      d.report.right=analogstates[RIGHT];   
      
      //read and write digital byte 1
      byte newbut0 = 0b00000000;
      digitalstates[0] = bitRead(r.buttons0, 0);
      bitWrite(newbut0, 0, digitalstates[A]);

      digitalstates[1] = bitRead(r.buttons0, 1);
      bitWrite(newbut0, 1, digitalstates[B]);

      digitalstates[2] = bitRead(r.buttons0, 2);
      bitWrite(newbut0, 2, digitalstates[X]);

      digitalstates[3] = bitRead(r.buttons0, 3);
      bitWrite(newbut0, 3, digitalstates[Y]);

      digitalstates[4] = bitRead(r.buttons0, 4);
      bitWrite(newbut0, 4, digitalstates[START]);

      bitWrite(newbut0, 5, bitRead(r.buttons0, 5));

      bitWrite(newbut0, 6, bitRead(r.buttons0, 6));

      bitWrite(newbut0, 7, bitRead(r.buttons0, 7));

      //read and write digital byte 2
      byte newbut1 = 0b00000000;
      digitalstates[5] = bitRead(r.buttons1, 0);
      bitWrite(newbut1, 0, digitalstates[DL]);

      digitalstates[6] = bitRead(r.buttons1, 1);
      bitWrite(newbut1, 1, digitalstates[DR]);

      digitalstates[7] = bitRead(r.buttons1, 2);
      bitWrite(newbut1, 2, digitalstates[DD]);

      digitalstates[8] = bitRead(r.buttons1, 3);
      bitWrite(newbut1, 3, digitalstates[DU]);

      digitalstates[9] = bitRead(r.buttons1, 4);
      bitWrite(newbut1, 4, digitalstates[Z]);

      digitalstates[10] = bitRead(r.buttons1, 5);
      bitWrite(newbut1, 5, digitalstates[R]);

      digitalstates[11] = bitRead(r.buttons1, 6);
      bitWrite(newbut1, 6, digitalstates[L]);

      bitWrite(newbut1, 7, bitRead(r.buttons1, 7));

      //write the bytes to a controller report
      d.report.buttons0 = newbut0;
      d.report.buttons1 = newbut1;

      //--------------------------------------
      //write the report to the gamecube
      GamecubeConsole1.write(d);   
      }
  }
}

void randomise(){
  //shuffle digitals
  uint8_t x[12];
  for (size_t i = 0; i < 12; i++) x[i] = i;
  for (size_t i = 0; i < 12; i++) {
    size_t j = random(i, 11);
  
    // swap x[i] and x[j]
    auto t = x[i];
    x[i] = x[j];
    x[j] = t;
  }
  //assign random button IDs
  A = x[0];
  B = x[1];
  X = x[2];
  Y = x[3];
  START = x[4];
  DL = x[5];
  DR = x[6];
  DU = x[7];
  DD = x[8];
  Z = x[9];
  R = x[10];
  L = x[11];

  //shuffle analogs
  uint8_t y[6];
  for (size_t i = 0; i < 6; i++) y[i] = i;
  for (size_t i = 0; i < 6; i++) {
    size_t j = random(i, 5);
  
    // swap x[i] and x[j]
    auto t = y[i];
    y[i] = y[j];
    y[j] = t;
  }
  //assign random analog button IDs
  XA = y[0];
  YA = y[1];
  CX = y[2];
  CY = y[3];
  LEFT = y[4];
  RIGHT = y[5];
}
