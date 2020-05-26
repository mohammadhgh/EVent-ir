#ifndef Trajectory_h
#define Trajectory_h

#include <math.h>
#include <Arduino.h>

class Trajectory
{
private:
    int resolution = 10;
    float deltaDegree = 0;
    float easeInFactor = 0;
    float easeOutFactor = 0;
    float x0 = 0;
    float x1 = 0;
    float x2 = 0;
    float x3 = 0;
    float cx = 0;
    float bx = 0;
    float ax = 0;
    float timeStep = 0;
    float endTime = 0;
    float *x;
    float *RPM;

public:
    Trajectory(int resolution, float deltaDegree, float easeInFactor, float easeOutFactor, float endTime);
    void updateRatios();
    void calcTrajec();
    void calcRPM();
    float getRPM(int index);
    int getResolution();
};

#endif
