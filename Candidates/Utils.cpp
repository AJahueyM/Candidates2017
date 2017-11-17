#include "Utils.h"

double modifiedMap(double x, double in_min, double in_max, double out_min, double out_max){
 double temp = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
 temp = (int) (4*temp + .5);
 return (double) temp/4;
}

