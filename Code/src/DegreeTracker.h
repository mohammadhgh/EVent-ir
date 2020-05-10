#ifndef DEGREE_TRACKER_H
#define DEGREE_TRACKER_H

#include "motor.h"

class DegreeTracker
{
private:
    float desiredDeltaDegree;
    float desiredDeltaTime;
    float passedDeltaDegree;
    float passedTime;
    float leftDeltaDegree;
    float leftTime;
    float desiredRPM;
    float definedpulsestep = 0;

public:
    DegreeTracker(float desiredDeltaDegree,float desiredDeltaTime);
    void updateTime(float timeStep);
    void updatePosition(int pulseCount);
    float updateDesiredRPM();
    void resetPosition(void);
    // bool stopIfTrue(void);
    // bool getLeftTime(void);
    float getLeftDeltaDegree(void);
    float getLeftTime(void);


};

#endif
