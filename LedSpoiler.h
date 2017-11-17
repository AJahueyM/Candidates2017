#ifndef __SPOILER_H_
#define __SPOILER_H_
#include "Arduino.h"
#include <ShiftRegister74HC595.h>

class LedSpoiler{
private:
  ShiftRegister74HC595& sr;
  
  int redPin = 5;
  int bluePin = 6;
public:
  LedSpoiler(ShiftRegister74HC595& sr);
  void setRed();
  void setBlue();
  void setOff();
};
#endif
