#include <ShiftRegister74HC595.h>

#include "DriveTrain.h"
#include "LedSpoiler.h"
#include "ColorSensor.h"

/************************************
*Codigo Express para Candidates 2017*
************************************/


LedSpoiler spoilerLed; // This is bad :c
ColorSensor colorSensor;
DriveTrain driveTrain;


void setup() {
     Serial.begin(115200);

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
