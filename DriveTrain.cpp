#include "DriveTrain.h"

DriveTrain::DriveTrain(){
   pinMode(motorA_1, OUTPUT);
   pinMode(motorA_2, OUTPUT);
   pinMode(motorB_1, OUTPUT);
   pinMode(motorB_2, OUTPUT);
}

void DriveTrain::setLeftMotors(double input){
   if(input > 0.0){
    motorA_1Output = modifiedMap(input,0.0,1.0, 0.0, 255.0);
    motorA_2Output = 0.0;
    Serial.println(motorA_1Output);
   }else if(input < 0.0){
    motorA_2Output = modifiedMap(fabs(input),0.0,1.0, 0.0, 255.0);
    motorA_1Output = 0.0;
    Serial.print(input);
    Serial.print(" ");
    Serial.println(motorA_2Output);

   }else{
    motorA_2Output = 0;
    motorA_1Output = 0;
   }
   
   analogWrite(motorA_2, motorA_2Output);
   analogWrite(motorA_1, motorA_1Output);

}

void DriveTrain::setRightMotors(double input){
   if(input > 0.0){
    motorB_1Output = modifiedMap(input,0.0,1.0, 0, 255);
    motorB_2Output = 0.0;
   }else if(input < 0.0){
    motorB_2Output = modifiedMap(fabs(input),0.0,1.0, 0, 255);
    motorB_1Output = 0.0;
   }else{
    motorB_2Output = 0;
    motorB_1Output = 0;
   }
   
   analogWrite(motorB_2, motorB_2Output);
   analogWrite(motorB_1, motorB_1Output);
}

void DriveTrain::driveStraight(double input){
  setRightMotors(input);
  setLeftMotors(input);
}
