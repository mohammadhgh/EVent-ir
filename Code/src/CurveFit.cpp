#include <CurveFit.h>

CurveFit::CurveFit(int degree, float *ratios)
{
    this->degree = degree;
    this->a0=ratios[0];
    this->a1=ratios[1];
    this->a2=ratios[2];
}

int CurveFit::fit(float x){
    if(x<5)
        x=5;
    float y=0;
    float x1 = a1*x;
    float x2 = a2*pow(x,2);  
    y = a0 + x1 + x2;  
    return round(y);    
}