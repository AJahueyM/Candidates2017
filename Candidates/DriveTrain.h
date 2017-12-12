#ifndef __DRIVETRAIN_H_
#define __DRIVETRAIN_H_

#include "Arduino.h"
#include "Utils.h"
#include <Wire.h>
#include "MPU6050.h"
#include "HC_SR04.h"


class DriveTrain{
private:
  float yaw = 0;
 
  // Timers
  unsigned long timer = 0;
  float timeStep = 0.01;
  const int motorA_1 = 11;
  const int motorA_2 = 10;
  const int motorB_1 = 6;
  const int motorB_2 = 5;

  double motorA_1Output = 0;
  double motorA_2Output = 0;
  double motorB_1Output = 0;
  double motorB_2Output = 0;
  float angDifference = 0;

  double previousError = 0.0;
  MPU6050 mpu;
public:
  DriveTrain();
  void update();
  int getYaw();
  void stop();
  void setLeftMotors(double input);
  void setRightMotors(double input);
  void drive(double input);
  void driveStraight(double input, int initAngle);
  void driveTimed(double input, int ms);
  void driveStraightTimed(double input, int initAngle,int ms);
  void driveStraightDistance(double input, int initAngle, int distance, HC_SR04& sensor);
  void resetAngle();
  void turn(double input);
  void turnToAngle(int angle);
};
#endif

