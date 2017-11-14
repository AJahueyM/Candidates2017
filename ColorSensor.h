#ifndef __COLORSENSOR_H_
#define __COLORSENSOR_H_
#include "Arduino.h"
#include <ShiftRegister74HC595.h>

enum Color {
  Red, 
  Blue,
  None
};
class ColorSensor{
private:
  int redFrequency = 0, blueFrequency = 0;
  const int S0 = 2;
  const int S1 =  1;
  const int  S2 = 3;
  const int  S3 = 4;
  const int sensorOut =  3;
  ShiftRegister74HC595& sr;

public:
  ColorSensor(ShiftRegister74HC595& sr);
  Color getColor();

};

#endif
