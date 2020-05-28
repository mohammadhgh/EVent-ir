#ifndef PID_H
#define PID_H
#include <Arduino.h>
#include <motor.h>
class PID
{
private:
    float KI;
    float KP;
    float KD;
    float error=0;
    float errorPre=0;
    float integral=0;
    float derivative=0;
    float realPidVal=0;
    int   minOutput=0;
    int   maxOutput=255;
    float timeStep=5e-3; //Unit is in Seconds
    float oldPWM=0;
    float ignorePIDCount=0;
    int   ignoreCounter=0;
    int   stepCounter=0;
    int   stepGaurd=0;
    int   initialPWM=0;
public:
    PID(float KP, float KI, float KD, int initialPWM, int ignorePIDCount, int stepGaurd);
    int   Calc(float desired, float pv);
    void  setTimeStep(float timeStep);
    float getTimeStep();
    float getError();
    float getPidRealVal();
    void  setOutputRange(int min, int max);
    float limitOutput(float input);
    void  resetParams();
};
#endif

