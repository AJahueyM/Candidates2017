#ifndef __DRIVETRAIN_H_
#define __DRIVETRAIN_H_

#include "Arduino.h"
#include "Utils.h"

class DriveTrain{
private:
  const int motorA_1 = 6;
  const int motorA_2 = 5;
  const int motorB_1 = 11;
  const int motorB_2 = 10;

  double motorA_1Output = 0;
  double motorA_2Output = 0;
  double motorB_1Output = 0;
  double motorB_2Output = 0;
public:
  DriveTrain();
  void setLeftMotors(double input);
  void setRightMotors(double input);
  void driveStraight(double input);
};
#endif
