#include "DegreeTracker.h"
DegreeTracker::DegreeTracker(float desiredDeltaDegree, float desiredDeltaTime, float timeStep)
{
    this->desiredDeltaDegree = desiredDeltaDegree;
    this->desiredDeltaTime   = desiredDeltaTime;
    this->passedDeltaDegree  = 0;
    this->passedTime         = 0;
    this->stepLeftDegree     = 0;
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

void DegreeTracker::updateDesiredDeltaDegree(float desiredDeltaDegree){
    this->desiredDeltaDegree = desiredDeltaDegree;
}


void DegreeTracker::updatePosition(int pulseCount)
{ 
    this->updateTime();
    this->passedDeltaDegree = pulseStep * (float)pulseCount;
    this->leftDeltaDegree   = this->desiredDeltaDegree - this->passedDeltaDegree;
}

void DegreeTracker::updateTime()
{
    this->passedTime +=  this->timeStep;
    this->leftTime   -=  this->timeStep;
}

float DegreeTracker::updateDesiredRPM(float motorRPM)
{
    desiredRPM = leftDeltaDegree/ (this->leftTime * 6);
    if(desiredRPM-motorRPM>2){
        stepLeftDegree += (desiredRPM - motorRPM)*6*timeStep;
    }
    else
    {
        stepLeftDegree = 0;
    }
    
    desiredRPM = (leftDeltaDegree + stepLeftDegree)/ (this->leftTime * 6);
    return desiredRPM;
}

void DegreeTracker::resetPosition(void)
{
    this->passedDeltaDegree = 0;
    this->passedTime        = 0;
    this->stepLeftDegree    = 0;
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

float DegreeTracker::getDesiredRPM(void)
{
    return this->desiredRPM;
}
