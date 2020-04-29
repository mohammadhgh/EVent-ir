#ifndef SYSCONFIG_H
#define SYSCONFIG_H

#include <Arduino.h>
#include <configuration.h>

#define AMBO_TOUCH_ANGLE        (float)16.34
#define COMPLETE_CLOSE_OMEGA    (float)41.46
#define AMBO_OPEN_OMEGA         (float)25.12
#define DEGREE_TO_RPM           (float)0.166667


class SysConfig
{
private:
    int IE_Ratio;
    int Resp_Rate;
    int Tidal_Volume;
    float Inhale_Time;
    float Exhale_Time;
    float MotorInhaleOmega=0;
    float MotorExhaleOmega=0;
    float MotorInhaleRPM=0;
    float MotorExhaleRPM=0;
    unsigned long Start_Time;

public:
    SysConfig(int IE_Ratio, int Resp_Rate, int Tidal_Volume);
    int get_IE_Ratio();
    int get_Resp_Rate();
    int get_Tidal_Volume();
    float get_Inh_Time();
    float get_Exh_Time();
    float get_Inhale_Omega();
    float get_Exhale_Omega();
    float get_Inhale_RPM();    
    float get_Exhale_RPM();    
    unsigned long get_Start_Time();
    void set_IE_Ratio(int IE_Ratio);
    void set_Resp_Rate(int Resp_Rate);
    void set_Tidal_Volume(int Tidal_Volume);
    void set_Inh_Time();
    void set_Exh_Time();
    void set_Motor_Omega();
    void set_Motor_RPM();
    void set_Start_Time();
    void update(SysConfig *new_config);
};

#endif