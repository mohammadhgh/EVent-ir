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
    float timeStep;
    float leftDeltaDegree;
    float leftTime;
    float desiredRPM;
    float definedpulsestep = 0;
    float pulseStep=0;
public:
    DegreeTracker(float desiredDeltaDegree, float desiredDeltaTime, float timeStep);
    void updateTime();
    void updatePosition(int pulseCount);
    float updateDesiredRPM();
    void resetPosition(void);
    // bool stopIfTrue(void);
    // bool getLeftTime(void);
    float getLeftDeltaDegree(void);
    float getLeftTime(void);


};

#endif
