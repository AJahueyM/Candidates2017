#include "ColorSensor.h"

ColorSensor::ColorSensor(ShiftRegister74HC595& sr) : sr(sr){
  sr.set(S0, HIGH); 
  sr.set(S1, LOW);
  pinMode(sensorOut, INPUT);
}

Color ColorSensor::getColor(){ 
  sr.set(S2,LOW);
  sr.set(S3,LOW);
  redFrequency = pulseIn(sensorOut, LOW);

 
  sr.set(S2,LOW);
  sr.set(S3,HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);

  if(redFrequency > 400 || blueFrequency > 400){
    return Color::None;
  }else if(redFrequency < blueFrequency){
    return Color::Red;
  }else if(redFrequency > blueFrequency){
     return Color::Blue;

  }
}

