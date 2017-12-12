#include "SR_74HC595.h"
SR_74HC595::SR_74HC595() : ShiftRegister74HC595(chipQuantity,serialDataPin,clockPin,latchPin){
    Serial.println("HI");
    setAllHigh();
}

