#include "DegreeTracker.h"
DegreeTracker::DegreeTracker(float desiredDeltaDegree, float desiredDeltaTime, float timeStep)
{
    this->desiredDeltaDegree = desiredDeltaDegree;
    this->desiredDeltaTime   = desiredDeltaTime;
    this->passedDeltaDegree  = 0;
    this->passedTime         = 0;
    this->timeStep           = timeStep;
    this->leftDeltaDegree    = desiredDeltaDegree;
    this->leftTime           = desiredDeltaTime;
    this->desiredRPM         = desiredDeltaDegree / (desiredDeltaTime * 6);
    this->pulseStep          = (float)360 / (float)MOTOR_PULSE_PER_TURN;
}

void DegreeTracker::updateDesiredDelatTime(float desiredDeltaTime)
{
    this->desiredDeltaTime = desiredDeltaTime;
}

void DegreeTracker::updateTime()
{
    this->passedTime +=  this->timeStep;
    this->leftTime   -=  this->timeStep;
}
void DegreeTracker::updatePosition(int pulseCount)
{ 
    this->passedDeltaDegree = pulseStep * (float)pulseCount;
    this->leftDeltaDegree   = this->desiredDeltaDegree - this->passedDeltaDegree;
}
float DegreeTracker::updateDesiredRPM()
{
    this->desiredRPM = this->leftDeltaDegree / (this->leftTime * 6);
    return this->desiredRPM;
}
void DegreeTracker::resetPosition(void)
{
    this->passedDeltaDegree = 0;
    this->passedTime        = 0;
    this->leftDeltaDegree   = desiredDeltaDegree;
    this->leftTime          = desiredDeltaTime;
    this->desiredRPM        = desiredDeltaDegree / (desiredDeltaTime * 6);
}

float DegreeTracker::getLeftDeltaDegree(void)
{
    return this->leftDeltaDegree;
}

float DegreeTracker::getLeftTime(void)
{
    return this->leftTime;
}
