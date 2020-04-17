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
public:
    SysConfig(int IE_Ratio, int Resp_Rate, int Tidal_Volume);
    int get_IE_Ratio();
    int get_Resp_Rate();
    int get_Tidal_Volume();
    void set_IE_Ratio(int IE_Ratio);
    void set_Resp_Rate(int Resp_Rate);
    void set_Tidal_Volume(int Tidal_Volume);
    void update(SysConfig* new_config);
};

#endif