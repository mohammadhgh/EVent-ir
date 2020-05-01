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
public:
    PID(float KI, float KP, float KD);
    int Calc(float desired, float pv);
    void resetParams();
};

