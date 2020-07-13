#include <CurveFit.h>
#include <MotorController.h>

CurveFit::CurveFit(int degree, float *ratios)
{
    this->degree = degree;
    this->a0=ratios[0];
    this->a1=ratios[1];
    this->a2=ratios[2];
}

int CurveFit::fit(float x, int minimumRpm){
    if(x<minimumRpm)
        x=minimumRpm;
    if(x>MAXIMUM_MOTOR_SPEED_IN_RPM)
        x=MAXIMUM_MOTOR_SPEED_IN_RPM;    
    float y=0;
    float x1 = a1*x;
    float x2 = a2*pow(x,2);  
    y = a0 + x1 + x2;  
    return round(y);    
}