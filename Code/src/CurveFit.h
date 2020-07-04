#ifndef CURVE_FIT_H
#define CURVE_FIT_H

#include <Arduino.h>
class CurveFit
{
private:
    int degree=0;
    float x =0;
    float a0=0;
    float a1=0;
    float a2=0;
public:
    CurveFit(int degree, float *ratios);
    int fit(float x, int minimumRpm);
    
};

#endif