#include "DriveTrain.h"

const int motor2_1 = 6;
const int motor2_2 = 5;
const int motor1_1 = 11;
const int motor1_2 = 10;

DriveTrain driveTrain(motor1_1, motor1_2, motor2_1, motor2_2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  driveTrain.driveStraight(0);        

}
