#include <ShiftRegister74HC595.h>

#include "DriveTrain.h"
#include "LedSpoiler.h"
#include "ColorSensor.h"

/************************************
*Codigo Express para Candidates 2017*
************************************/



int serialDataPin = 8; // DS
int clockPin = 9; // SHCP
int latchPin = 12; // STCP
int chipQuantity =  1;


ShiftRegister74HC595 sr (chipQuantity, serialDataPin, clockPin, latchPin);
LedSpoiler spoilerLed(sr); // This is bad :c
ColorSensor colorSensor(sr);
DriveTrain driveTrain;


void setup() {
  driveTrain.driveStraight(0);
}

void loop() {
  Color color = colorSensor.getColor();
  if(color == Color::Red){
    spoilerLed.setRed();
  }else if(color == Color::Blue){
    spoilerLed.setBlue();
  }else{
    spoilerLed.setOff();
  }
  
}
