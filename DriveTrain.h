#include "Arduino.h"
#include "Utils.h"

class DriveTrain{
private:
  double motorA_1Output = 0;
  double motorA_2Output = 0;
  double motorB_1Output = 0;
  double motorB_2Output = 0;
  int motorA_1, motorA_2, motorB_1, motorB_2;
public:
  DriveTrain(int motorA_1, int motorA_2, int motorB_1, int motorB_2);
  void setLeftMotors(double input);
  void setRightMotors(double input);
  void driveStraight(double input);
};

