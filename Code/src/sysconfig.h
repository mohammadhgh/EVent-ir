#ifndef SYSCONFIG_H
#define SYSCONFIG_H

#include <Arduino.h>
#include <configuration.h>

class SysConfig
{
private:
    int IE_Ratio;
    int Resp_Rate;
    int Tidal_Volume;
    int Inhale_Time;
    int Exhale_Time;
    unsigned long Start_Time;
  
public:
    float duration  = 1;
    int   loopParam = 4;
    float timeStep  = 5e-3; 
    int   resolution = 0; 
    float *calcedRPM;
    SysConfig(int IE_Ratio, int Resp_Rate, int Tidal_Volume);
    int get_IE_Ratio();
    int get_Resp_Rate();
    int get_Tidal_Volume();
    int get_Inh_Time();
    int get_Exh_Time();
    unsigned long get_Start_Time();
    void set_loopParams(float duration, int  loopParam, float  timeStep);
    void set_IE_Ratio(int IE_Ratio);
    void set_Resp_Rate(int Resp_Rate);
    void set_Tidal_Volume(int Tidal_Volume);
    void set_Inh_Time();
    void set_Exh_Time();
    void set_Start_Time();
    void update(SysConfig *new_config);
};

#endif