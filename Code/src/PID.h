#include <Arduino.h>
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
    float lastIntegral=0;
    int   minOutput=0;
    int   maxOutput=255;
public:
    PID(float KI, float KP, float KD);
    int Calc(float desired, float pv);
    void setOutputRange(int min, int max);
    float limitOutput(float input);
    void resetParams();
};

