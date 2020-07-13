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
    float stepLeftDegree;
    float leftDeltaDegree;
    float leftTime;
    float desiredRPM;
    float definedpulsestep = 0;
    float pulseStep=0;
public:
    DegreeTracker(float desiredDeltaDegree, float desiredDeltaTime, float timeStep);
    void updateDesiredDeltaDegree(float desiredDeltaDegree);
    void updateDesiredDelatTime(float desiredDeltaTime);
    void updateTime();
    void updatePosition(int pulseCount);
    float updateDesiredRPM(float motorRPM);
    void resetPosition(void);
    float getLeftDeltaDegree(void);
    float getLeftTime(void);
    float getDesiredRPM(void);


};

#endif
