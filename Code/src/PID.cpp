
#include <PID.h>

PID::PID(float KP, float KI, float KD, int ignorePIDCount){
    this->KP=KP;
    this->KI=KI;
    this->KD=KD;
    this->ignorePIDCount = ignorePIDCount;
}

int PID::Calc(float desired, float pv){
    float pwm = 0;
    if(ignoreCounter==0)
    {
        pwm = 20;
        oldPWM = pwm;
    }
    if(ignoreCounter>ignorePIDCount)
    {
        error = desired - pv;

        integral += error*timeStep;

        derivative = (error - errorPre)/timeStep;

        errorPre = error;
        
        //pwm = 255 - (KP*error + KI*integral + KD*derivative);  
        
        pwm = KP*error + KI*integral + KD*derivative;  

        realPidVal = pwm ; 

        pwm = limitOutput(pwm);

        oldPWM = pwm;
    }
    
    ignoreCounter++;

    return round(oldPWM); 
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
    this->ignoreCounter=0;
}
