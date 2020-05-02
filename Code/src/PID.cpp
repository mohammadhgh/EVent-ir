
#include <PID.h>
char tbp[20]="";
PID::PID(float KI, float KP, float KD){
    this->KP=KP;
    this->KI=KI;
    this->KD=KD;
}

int PID::Calc(float desired, float pv){
    error = desired - pv;
    //Serial.println("error");
    //Serial.println(error);
    
    integral = (error+integral)*(float)0.2;
    
    derivative = (error - errorPre)/(float)0.2;
    
    float pwm = KP*error + KI*integral + KD*derivative;
    //Serial.println("unlimited");
    //Serial.println(pwm);
    sprintf(tbp,"%ld\t%ld\t%ld",round(desired*100), round(pv*100), round(pwm*100));
    Serial.println(tbp);
    errorPre = error;

    pwm = limitOutput(pwm);
    pwm = 255 - pwm;
    //Serial.println("final");
    //Serial.println(pwm);
    return round(pwm); 
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
    this->lastIntegral=0;
}
