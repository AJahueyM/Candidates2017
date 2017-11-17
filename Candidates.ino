#include <ShiftRegister74HC595.h>

#include "DriveTrain.h"
#include "LedSpoiler.h"
#include "ColorSensor.h"




/************************************
*Codigo Express para Candidates 2017*
************************************/
  int chipQuantity = 2;
  int serialDataPin = 8;
  int clockPin = 9;
  int latchPin = 12;
  ShiftRegister74HC595 sr(chipQuantity, serialDataPin, clockPin, latchPin);
  
  LedSpoiler* spoilerLed;
  ColorSensor* colorSensor;
  DriveTrain* driveTrain;
  double initAngle = 0;

void setup() {
  Serial.begin(115200);
  spoilerLed = new LedSpoiler(sr);
  colorSensor = new ColorSensor(sr);
  driveTrain = new DriveTrain;
  initAngle = driveTrain->getYaw();
}

void loop() {
  driveTrain->update();
  Color color = colorSensor->getColor();
  if(color == Color::Red){
    spoilerLed->setRed();
  }else if(color == Color::Blue){
    spoilerLed->setBlue();
  }else{
    spoilerLed->setOff();
  }
  int initTime = millis();
  initAngle = driveTrain->getYaw();
  while(millis() - initTime < 5000){
    driveTrain->driveStraight(.75, initAngle);
  }
  driveTrain->turnToAngle(-70);
  initAngle = driveTrain->getYaw();
  initTime = millis();
  while(millis() - initTime < 5000){
    driveTrain->driveStraight(.75, initAngle);
  }
}
