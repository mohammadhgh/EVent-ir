#include <trajectory.h>

Trajectory::Trajectory(int resolution,float deltaDegree,float easeInFactor,float easeOutFactor, float endTime)
{
    this->resolution    = resolution ;
    this->deltaDegree   = deltaDegree ;
    this->easeInFactor  = easeInFactor ;
    this->easeOutFactor = easeOutFactor;
    this->endTime       = endTime;
    this->x   = new float[resolution+1];
    this->RPM = new float[resolution+1]; 
    updateRatios();
}

void Trajectory::updateRatios(){
    x1=deltaDegree*(easeInFactor);
    x2=deltaDegree*(1-easeOutFactor);
    x3=x0+deltaDegree; 

    cx = 3  * (x1 - x0);
    bx = 3  * (x2 - x1) - cx;
    ax = x3 -  x0 - cx  - bx;

    timeStep = endTime/resolution;
   
}

void Trajectory::calcTrajec(){
    for(int i=0; i<=resolution; i++){
        x[i] = ax*pow(i*timeStep,3) + bx*pow(i*timeStep,2) + cx*i*timeStep + x0;
    }
    calcRPM();
}

void Trajectory::calcRPM(){
    for(int i=0; i<resolution;i++){
        RPM[i]=(x[i+1]-x[i])/timeStep;
    } 
}

float Trajectory::getRPM(int index){
    return RPM[index];
}
