#include "HC_SR04.h"
#include <Arduino.h>

HC_SR04::HC_SR04(int pinTrigger, int pinEcho){
  this -> pinTrigger = pinTrigger;
  this -> pinEcho = pinEcho;

  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
}

long HC_SR04:: getDistance(){
  long duration;
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10); 
  digitalWrite(pinTrigger, LOW);
  duration = pulseIn(pinEcho, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}

