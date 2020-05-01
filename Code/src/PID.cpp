
#include <PID.h>

PID::PID(float KI, float KP, float KD){
    this->KP=KP;
    this->KI=KI;
    this->KD=KD;
}

int PID::Calc(float desired, float pv){
    error = desired - pv;
    
    integral += error;
    
    derivative = error - errorPre;
    
    float pwm = KP*error + KI*integral + KD*derivative;
    Serial.println(pwm);
    errorPre = error;
    if (pwm>255)
        pwm = 255;
    if (pwm<0)
        pwm = 0; 
    return pwm; 
}
void PID::resetParams(){
    float error=0;
    float errorPre=0;
    float integral=0;
    float derivative=0;
    float lastIntegral=0;
}