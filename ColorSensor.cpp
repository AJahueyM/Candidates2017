#include "ColorSensor.h"

ColorSensor::ColorSensor(ShiftRegister74HC595& sr) : sr(sr){
  sr.set(S0, HIGH); 
  sr.set(S1, LOW);
  pinMode(sensorOut, INPUT);
}
bool ColorSensor::withinRange(int input, int value){
  if(input + input * range > value && input - input*range < value)    
    return true;
  return false;
}

Color ColorSensor::getColor(){ 
  
  sr.set(S2,LOW);
  sr.set(S3,LOW);
  redFrequency = map(pulseIn(sensorOut, LOW), 152, 27, 0, 255);
  //redFrequency = pulseIn(sensorOut, LOW);

 
  sr.set(S2,LOW);
  sr.set(S3,HIGH);
  blueFrequency = map(pulseIn(sensorOut, LOW), 142, 23, 0, 255);
  //blueFrequency = pulseIn(sensorOut, LOW);

  
  sr.set(S2,HIGH);
  sr.set(S3,HIGH);
  greenFrequency = map(pulseIn(sensorOut, LOW), 171, 23, 0, 255);
  //greenFrequency = pulseIn(sensorOut, LOW);
  if(redFrequency < 1){
     redFrequency = 1;
  }
  if(greenFrequency < 1){
     greenFrequency = 1;
  }
  if(blueFrequency < 1){
     blueFrequency = 1;
  }
   Serial.print("R= ");
  Serial.print(redFrequency);
  Serial.print(" G= ");
  Serial.print(greenFrequency);
  Serial.print(" B= ");
  Serial.println(blueFrequency);

  if((withinRange(redFrequency, 283)&& withinRange(greenFrequency, 156))&& withinRange(blueFrequency, 233)){
      Serial.print("PINK");
      return Color::Pink;
  }else if((withinRange(redFrequency, 285)&& withinRange(greenFrequency, 215))&& withinRange(blueFrequency, 170)){
      Serial.print("ORANGE");
      return Color::Orange;
  }else if((withinRange(redFrequency, 261)&& withinRange(greenFrequency, 253))&& withinRange(blueFrequency, 190)){
      Serial.print("YELLOW");
      return Color::Yellow;
  }else if(redFrequency > blueFrequency){
      Serial.print("RED");
      return Color::Red;
  }else if(blueFrequency > redFrequency){
      Serial.print("BLUE");
      return Color::Blue;
  }else{
      return Color::None;
  }
}

