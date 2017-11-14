#include "ColorSensor.h"

ColorSensor::ColorSensor(ShiftRegister74HC595& sr) : sr(sr){
  sr.set(S0, HIGH); 
  sr.set(S1, LOW);
  pinMode(sensorOut, INPUT);
}

Color ColorSensor::getColor(){ 
  sr.set(S2,LOW);
  sr.set(S3,LOW);
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(redFrequency);//printing RED color frequency
  Serial.print("  ");
 
  // Setting Blue filtered photodiodes to be read
  sr.set(S2,LOW);
  sr.set(S3,HIGH);
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(blueFrequency);//printing RED color frequency
  Serial.println("  ");

  if(redFrequency > 400 || blueFrequency > 400){
    return Color::None;
  }else if(redFrequency < blueFrequency){
    return Color::Red;
  }else if(redFrequency > blueFrequency){
     return Color::Blue;

  }
}

