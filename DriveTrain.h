#ifndef __DRIVETRAIN_H_
#define __DRIVETRAIN_H_

#include "Arduino.h"
#include "Utils.h"
#include <Wire.h>
#include "MPU6050.h"
class DriveTrain{
private:
  // Timers
  unsigned long timer = 0;
  float timeStep = 0.01;
  
  // Pitch, Roll and Yaw values
  float pitch = 0;
  float roll = 0;
  float yaw = 0;
  
  MPU6050 mpu;


  const int motorA_1 = 11;
  const int motorA_2 = 10;
  const int motorB_1 = 6;
  const int motorB_2 = 5;

  double motorA_1Output = 0;
  double motorA_2Output = 0;
  double motorB_1Output = 0;
  double motorB_2Output = 0;
public:
  DriveTrain();
  void update();
  int getYaw();
  void setLeftMotors(double input);
  void setRightMotors(double input);
  void driveStraight(double input, int initAngle);
  void turn(double input);
  void turnToAngle(int angle);
};
#endif
