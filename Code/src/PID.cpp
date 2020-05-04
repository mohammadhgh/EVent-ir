
#include <PID.h>

PID::PID(float KP, float KI, float KD){
    this->KP=KP;
    this->KI=KI;
    this->KD=KD;
}

int PID::Calc(float desired, float pv){
    error = desired - pv;

    integral = abs(error) < 20 ? integral + error*timeStep : integral;

    derivative = (error - errorPre)/timeStep;

    errorPre = error;
    
    float pwm = 255 - (KP*error + KI*integral + KD*derivative);
    realPidVal = pwm ; 

    pwm = limitOutput(pwm);

    return round(pwm); 
}

void PID::setTimeStep(float timeStep){
    this->timeStep=timeStep;
}

float PID::getTimeStep(){
    return this->timeStep;
}

float PID::getError(){
    return this->error;
}

float PID::getPidRealVal(){
    return this->realPidVal;
}

void PID::setOutputRange(int min, int max)
{
    this->minOutput=min;
    this->maxOutput=max;
}

float PID::limitOutput(float input){
    if (input>maxOutput)
        return maxOutput;
    if (input<minOutput)
        return minOutput; 
    return input;
}

void PID::resetParams(){
    this->error=0;
    this->errorPre=0;
    this->integral=0;
    this->derivative=0;
}
