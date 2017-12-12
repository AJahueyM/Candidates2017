
#ifndef __SR_74HC595_H_
#define __SR_74HC595_H_

#include <ShiftRegister74HC595.h>
#include "Arduino.h"

class SR_74HC595 : public ShiftRegister74HC595{

private:
  int chipQuantity = 2;
  int serialDataPin = 8;
  int clockPin = 9;
  int latchPin = 12;

  SR_74HC595();
  SR_74HC595(const SR_74HC595 &);
  SR_74HC595 &operator=(const SR_74HC595 &);

public:

  static SR_74HC595 &getInstance() {
    static SR_74HC595 singletonInstance;
    return singletonInstance;
  }
};

#endif

