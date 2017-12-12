#include "DriveTrain.h"

DriveTrain::DriveTrain(){
   pinMode(motorA_1, OUTPUT);
   pinMode(motorA_2, OUTPUT);
   pinMode(motorB_1, OUTPUT);
   pinMode(motorB_2, OUTPUT);
   
  Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // If you want, you can set gyroscope offsets
  // mpu.setGyroOffsetX(155);
  // mpu.setGyroOffsetY(15);
  // mpu.setGyroOffsetZ(15);
  
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
void DriveTrain::stop(){
    setRightMotors(0);
    setLeftMotors(0);
}
void DriveTrain::driveTimed(double input, int ms){
 int startTime = millis();
  while(millis() - startTime < ms){
     setRightMotors(input);
     setLeftMotors(input);
  
  }
  stop();
}
void DriveTrain::drive(double input){
     setRightMotors(input);
     setLeftMotors(input);
}
void DriveTrain::driveStraight(double input, int initAngle){
  update();
  double error = initAngle - getYaw();
  double mul = error /(abs(getYaw() + 1));
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
void DriveTrain::driveStraightTimed(double input, int initAngle, int ms){
  int startTime = millis();
  while(millis() - startTime < ms){
    driveStraight(input, initAngle);
  }
  stop();
}
void DriveTrain::driveStraightDistance(double input, int initAngle, int distance, HC_SR04& sensor ){
      double distanceSensor = sensor.getDistance();
      double errorDistance = distanceSensor -distance;
      while(abs(errorDistance) != 0){
       distanceSensor = sensor.getDistance();
       errorDistance = distanceSensor - distance;
       driveStraight(errorDistance / 10.0, initAngle);
       delay(16);
      }
      stop();
}
void DriveTrain::resetAngle(){
  angDifference = -yaw;
}
int DriveTrain::getYaw(){
  update();
  int baseAngle = -yaw - angDifference;

  int finalAngle = baseAngle;
  int vueltas  = baseAngle / 180;

  if(baseAngle > 180){
      if(vueltas % 2 == 0){
        finalAngle = (abs(baseAngle) % 180);
      }else{
        finalAngle = -180 + (abs(baseAngle) % 180);
      }
  }else if(baseAngle < -180){
    if(vueltas % 2 == 0){
      finalAngle = -1*(abs(baseAngle) % 180);  
    }else{
      finalAngle = 180 - (abs(baseAngle)%180);
    }
  }
  return finalAngle;
}
void DriveTrain::turn(double input){
    setRightMotors(-input);
    setLeftMotors(input);

}
void DriveTrain::turnToAngle(int angle){
    update();
    int mod = abs(angle) % 180;

    if(angle > 180){
      angle = -180 + mod; 
    }else if(angle < -180){
      angle = 180 - mod; 
    }
    int error = angle - getYaw();
    while(error != 0){
      update();
      error = angle - getYaw();

      double mul = (error / 180.0) * 10.0;
      if(mul > 1.0){
        mul = 1.0;
      }else if(mul < -1.0){
        mul = -1.0;
      }else if(mul <= .25 && mul >= 0.0){
        mul  = .25;
      }else if(mul >= -.25 && mul <= 0.0){
        mul = -.25;
      }
      turn(mul);
    }
    turn(0);
}


