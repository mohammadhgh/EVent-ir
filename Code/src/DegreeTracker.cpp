#include "DegreeTracker.h"
DegreeTracker::DegreeTracker(float desiredDeltaDegree, float desiredDeltaTime)
{
    this->desiredDeltaDegree = desiredDeltaDegree;
    this->desiredDeltaTime = desiredDeltaTime;
    this->passedDeltaDegree = 0;
    this->passedTime = 0;
    this->leftDeltaDegree = desiredDeltaDegree;
    this->leftTime = desiredDeltaTime;
    this->desiredRPM = desiredDeltaDegree / (desiredDeltaTime * 60);
}

void DegreeTracker::updateTime(float timeStep)
{
    this->passedTime += timeStep;
    this->leftTime -= timeStep;
}
void DegreeTracker::updatePosition(int pulseCount)
{
    float pulseStep = (float)360 / (float)MOTOR_PULSE_PER_TURN;
    this->definedpulsestep = pulseStep;
    // Serial.print("\n ******");
    // Serial.print(pulseStep);
    // Serial.print("\n ******");
    // Serial.print(pulseCount);
    // Serial.print("\n ******");
    this->passedDeltaDegree = pulseStep * (float)pulseCount;
    this->leftDeltaDegree = this->desiredDeltaDegree - this->passedDeltaDegree;
}
float DegreeTracker::updateDesiredRPM()
{
    this->desiredRPM = this->leftDeltaDegree / (this->leftTime * 6);
    return this->desiredRPM;
}
void DegreeTracker::resetPosition(void)
{
    this->passedDeltaDegree = 0;
    this->passedTime = 0;
    this->leftDeltaDegree = desiredDeltaDegree;
    this->leftTime = desiredDeltaTime;
    this->desiredRPM = desiredDeltaDegree / (desiredDeltaTime * 6);
}
// bool DegreeTracker::stopIfTrue(void)
// {
//     if (this->leftDeltaDegree < 2)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }

// bool DegreeTracker::getLeftTime(void)
// {
//     if (this->leftDeltaDegree <= 0)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }

float DegreeTracker::getLeftDeltaDegree(void)
{
    return this->leftDeltaDegree;
}

float DegreeTracker::getLeftTime(void)
{
    return this->leftTime;
}
