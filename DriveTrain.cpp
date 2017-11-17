#include "DriveTrain.h"

DriveTrain::DriveTrain(){
   pinMode(motorA_1, OUTPUT);
   pinMode(motorA_2, OUTPUT);
   pinMode(motorB_1, OUTPUT);
   pinMode(motorB_2, OUTPUT);

     // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
}

void DriveTrain::update(){
  timer = millis();

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  yaw = yaw + norm.ZAxis * timeStep;
  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));

}
void DriveTrain::setLeftMotors(double input){
   if(input > 0.0){
    motorA_1Output = modifiedMap(input,0.0,1.0, 0.0, 255.0);
    motorA_2Output = 0.0;
   }else if(input < 0.0){
    motorA_2Output = modifiedMap(fabs(input),0.0,1.0, 0.0, 255.0);
    motorA_1Output = 0.0;
   }else{
    motorA_2Output = 0;
    motorA_1Output = 0;
   }
   
   analogWrite(motorA_2, motorA_2Output);
   analogWrite(motorA_1, motorA_1Output);

}

void DriveTrain::setRightMotors(double input){
   if(input > 0.0){
    motorB_2Output = modifiedMap(input,0.0,1.0, 0.0, 255.0);
    motorB_1Output = 0.0;
   }else if(input < 0.0){
    motorB_1Output = modifiedMap(fabs(input),0.0,1.0, 0.0, 255.0);
    motorB_2Output = 0.0;
   }else{
    motorB_2Output = 0;
    motorB_1Output = 0;
   }
   
   analogWrite(motorB_2, motorB_2Output);
   analogWrite(motorB_1, motorB_1Output);
}

void DriveTrain::driveStraight(double input, int initAngle){
  update();
  double error = initAngle - getYaw();
  double mul = (error / 25.0) * 7.0;
    if(mul > 1.0){
      mul = 1.0;
    }else if(mul < -1.0){
      mul = -1.0;
    }
  if(input >0){
   setRightMotors(input * (1.0 - mul));
   setLeftMotors(input * (1.0 + mul));
  }else{
   setRightMotors(input * (1.0 + mul));
   setLeftMotors(input * (1.0 - mul));   
  }
}
int DriveTrain::getYaw(){
  return -yaw;
}
void DriveTrain::turn(double input){
    setRightMotors(-input);
    setLeftMotors(input);

}
void DriveTrain::turnToAngle(int angle){
    int error = angle - getYaw();
    while(error != 0){
      update();
      Serial.println(error);
      error = angle - getYaw();
      double mul = (error / 180.0) * 10.0;
      if(mul > 1.0){
        mul = 1.0;
      }else if(mul < -1.0){
        mul = -1.0;
      }else if(mul < .15 && mul > 0.0){
        mul  = .15;
      }else if(mul > -.15 && mul < 0.0){
        mul = -.15;
      }
      turn(mul);
    }
    turn(0);
}

