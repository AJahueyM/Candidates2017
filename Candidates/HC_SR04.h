#ifndef __HC_SR04_H_
#define __HC_SR04_H_
#include <Arduino.h>

class HC_SR04{
  
  private:
    int distance;
    int pinTrigger, pinEcho;
  public:
    int getDistance();
    HC_SR04(int pinTrigger, int pinEcho);

};
#endif

