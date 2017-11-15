#ifndef __SPOILER_H_
#define __SPOILER_H_
#include "Arduino.h"
#include "SR_74HC595.h"
/**********************
* pls 4give this class*
***********************/

class LedSpoiler{
private:
  SR_74HC595& sr = SR_74HC595::getInstance();
  
  int redPin = 5;
  int bluePin = 6;
public:
  LedSpoiler();
  void setRed();
  void setBlue();
  void setOff();
};
#endif
