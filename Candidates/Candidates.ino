#include <ShiftRegister74HC595.h>

#include "DriveTrain.h"
#include "LedSpoiler.h"
#include "ColorSensor.h"
#include "HC_SR04.h"
#include "limits.h"

/************************************
  Codigo Express para Candidates 2017
************************************/
int chipQuantity = 2;
int serialDataPin = 8;
int clockPin = 9;
int latchPin = 12;
ShiftRegister74HC595 sr(chipQuantity, serialDataPin, clockPin, latchPin);
HC_SR04 sensorFront(7, 4);
HC_SR04 sensorLeft(7, 13);
HC_SR04 sensorRight(7, 2);;


LedSpoiler spoilerLed(sr);
ColorSensor colorSensor(sr);
DriveTrain* driveTrain;
bool ran = false;

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
//
enum Zones {
  Zona0,
  Zona1,
  Zona2,
  Zona3
};
//bool zone3 = false;
Zones currentZone;

bool zone3 = false;


void setup() {
  Serial.begin(9600);
  Color color = colorSensor.getColor();
  switch (color) {
    case Pink:
      currentZone = Zona1;
      break;
    case Yellow:
      currentZone = Zona3;
      break;
    case Red:
      currentZone = Zona1;
      break;
    case Blue:
      currentZone = Zona1;
      break;
    default:
      currentZone = Zona0;
      break;
  }
     currentZone = Zona1;

  driveTrain = new DriveTrain;
  spoilerLed.setRed();
}

void loop() {
  driveTrain->update();
  spoilerLed.setBlue();
  //Serial.println(driveTrain.getYaw());
  const int zone0DistanceWall = 35;
  const int zon0to1WallDistance = 5;
  const double zone0Speed = .25;
  Color color = colorSensor.getColor();
  int lineMemory[2];
  int sideTracker = 1; // 1 como izquierda

  while (currentZone == Zona0) {
    spoilerLed.setRed();
    Color color = colorSensor.getColor();
    int distance = sensorFront.getDistance();

    if (color != Black)
      driveTrain->driveStraight(zone0Speed, 0);
    else {
      driveTrain->stop();
      driveTrain->driveStraightTimed(-.25, 0, 1000);
      driveTrain->turnToAngle(90 * sideTracker);
      delay(1500);
      bool foundBlack = false;
      driveTrain->drive(-.5);
      delay(2000);
      int start = millis();
      
      while(millis() - start < 3500){
        driveTrain->driveStraight(.25, 90 * sideTracker);
        color = colorSensor.getColor();
        if(color == Black){
          spoilerLed.setBlue();
          driveTrain->stop();
          foundBlack = true;
          delay(1000);
          break;
        }
      }
      bool started = false;
      int timeBase = millis();
      int totalTime = timeBase;
      while(foundBlack){
        if(!started){
          driveTrain->turnToAngle(75 * sideTracker);
          started = true;
        }else{
           driveTrain->turnToAngle(-35 * sideTracker);
        }
        if(sideTracker == 1){
          driveTrain->setRightMotors(-.6);
          driveTrain->setLeftMotors(-.2);
        }else{
          driveTrain->setRightMotors(-.2);
          driveTrain->setLeftMotors(-.6);
        }
        delay(3000);
        driveTrain->resetAngle();
        
        while(colorSensor.getColor() != Black ){
          if(sensorFront.getDistance() <= 10){
            foundBlack = false;
              driveTrain->turnToAngle(-90 * sideTracker);
              driveTrain->resetAngle();
              break;
          }
          driveTrain->driveStraight(.25, driveTrain->getYaw());
        }
        driveTrain->stop();
      }
      driveTrain->turnToAngle(0);
      sideTracker *= -1;
    }
        if(distance < 5){
          driveTrain->driveStraightTimed(-zone0Speed, 0,500);
          driveTrain->turnToAngle(-90);
          driveTrain->drive(-.5);
          delay(2000);
          
          while(color != Pink){
            color = colorSensor.getColor();
            driveTrain->driveStraight(.25, -90);
          }
          driveTrain->stop();
    
          driveTrain->driveStraightDistance(zone0Speed, -90, 5, sensorFront);
          driveTrain->resetAngle();
          currentZone = Zona1;
        }
    //
    //    if(color == Color::Black){
    //      driveTrain->driveStraightTimed(-zone0Speed, 0, 1000);
    //      driveTrain->turnToAngle(90 * sideTracker);
    //      driveTrain->driveStraightDistance(zone0Speed, 90 * sideTracker, zone0DistanceWall, sensorFront);
    //      driveTrain->turnToAngle(0);
    //      sideTracker *= -1;
    //    }
  }

  int currentAngle = driveTrain->getYaw();
  
  while (currentZone == Zona1 ) {
    driveTrain->update();
    //int distanceFront = sensorFront.getDistance();
    Color color = colorSensor.getColor();
    switch (color) {
      case Red:
        spoilerLed.setRed();
        break;
      case Blue:
        spoilerLed.setBlue();
        break;
      default:
        spoilerLed.setOff();
        break;
    };
//    if (distanceFront < 5 && distanceFront > 0) {
//      driveTrain->stop();
//      if (sensorLeft.getDistance() < 15 && sensorRight.getDistance() < 15) {
//        currentAngle = driveTrain->getYaw();
//        driveTrain->driveStraight(-.25, currentAngle);
//        delay(2600);
//        driveTrain->stop();
//      }
//      if (sensorRight.getDistance() < 15 && sensorLeft.getDistance() > 15) {
//        driveTrain->turnToAngle(driveTrain->getYaw() - 90);
//        driveTrain->setLeftMotors(-.5);
//        driveTrain->setRightMotors(-.5);
//        delay(2500);
//        currentAngle = driveTrain->getYaw();
//      } else if (sensorLeft.getDistance() < 15 && sensorRight.getDistance() > 15) {
//        driveTrain->turnToAngle(driveTrain->getYaw() + 90);
//        driveTrain->setLeftMotors(-.5);
//        driveTrain->setRightMotors(-.5);
//        delay(2500);
//        currentAngle = driveTrain->getYaw();
//      }
//    } else {
//      driveTrain->driveStraight(.25, 0);
//    }
    if(sensorFront.getDistance() > 5){
      driveTrain->driveStraight(.25, 0);
    }else{
      driveTrain->stop();
      int rightDistance = 0, leftDistance = 0;
      driveTrain->turnToAngle(90);
        rightDistance = sensorFront.getDistance();
      driveTrain->turnToAngle(-90);
      leftDistance = sensorFront.getDistance();

      if(rightDistance>15){
          driveTrain->turnToAngle( 90);
          driveTrain->resetAngle();
          driveTrain->drive(-.5);
          delay(2000);
      }else if(leftDistance > 15){
          driveTrain->turnToAngle(- 90);
          driveTrain->resetAngle();
          driveTrain->drive(-.5);
          delay(2000);
      }else if(leftDistance < 10 && rightDistance < 10){
        driveTrain->driveStraightTimed(-.25, 0, 1500);
        int rightDistance = 0, leftDistance = 0;
        driveTrain->turnToAngle(90);
        rightDistance = sensorFront.getDistance();
        driveTrain->turnToAngle(-90);
        leftDistance = sensorFront.getDistance();
            if(rightDistance>15){
              driveTrain->turnToAngle( 90);
              driveTrain->resetAngle();
              driveTrain->drive(-.5);
              delay(2000);
          }else if(leftDistance > 15){
              driveTrain->turnToAngle(- 90);
              driveTrain->resetAngle();
              driveTrain->drive(-.5);
              delay(2000);
          }
      }

    }
  }

  if (currentZone == Zona3 && !zone3 ) {
    Color color = colorSensor.getColor();
    int arraySize = 66;
    driveTrain->resetAngle();
    spoilerLed.setBlue();
    driveTrain->driveStraightTimed(.25, 0,1000);
    driveTrain->driveTimed(-.25, 250);
    driveTrain->turnToAngle(90);
    driveTrain->drive(-.5);
    delay(1500);
    driveTrain->resetAngle();
    driveTrain->driveStraightTimed(.5, 0, 10000);
    driveTrain->driveStraightTimed(-.25, 0, 100);

    driveTrain->turnToAngle(-90);
 
    while (color != Black) {
      color = colorSensor.getColor();
      driveTrain->driveStraight(.25, driveTrain->getYaw());
    }
    driveTrain->stop();

    driveTrain->driveStraightTimed(.25, driveTrain->getYaw(), 1200  );

    driveTrain->stop();
    driveTrain->turnToAngle(driveTrain->getYaw() - 5);
    int readings[arraySize][2];
    int initAngle = driveTrain->getYaw();
    int minimum = INT_MAX;
    int angle = 0;
    for (int i = 0; i < arraySize ; ++i) {
      driveTrain->update();
      driveTrain->turnToAngle(driveTrain->getYaw() + 1 );
      readings[i][0] = driveTrain->getYaw();
      readings[i][1] = sensorFront.getDistance();
      if (readings[i][1] < minimum) {
        angle = readings[i][0];
        minimum = readings[i][1];
      }
    }
    driveTrain->turnToAngle(angle);
    driveTrain->stop();
    zone3 = true;
  }
}

