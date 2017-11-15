#ifndef __COLORSENSOR_H_
#define __COLORSENSOR_H_
#include "Arduino.h"
#include "SR_74HC595.h"

enum Color {
  Red, 
  Blue,
  None
};
class ColorSensor{
private:
  SR_74HC595& sr = SR_74HC595::getInstance();
  int redFrequency = 0, blueFrequency = 0;
  const int S0 = 2;
  const int S1 =  1;
  const int  S2 = 3;
  const int  S3 = 4;
  const int sensorOut =  3;

public:
  ColorSensor();
  Color getColor();

};

#endif
