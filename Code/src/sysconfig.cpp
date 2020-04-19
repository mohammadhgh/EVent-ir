#include <sysconfig.h>
#include <math.h>

SysConfig::SysConfig(int IE_Ratio, int Resp_Rate, int Tidal_Volume)
{
    this->IE_Ratio = IE_Ratio;
    this->Resp_Rate = Resp_Rate;
    this->Tidal_Volume = Tidal_Volume;
    this->Inhale_Time = 0;
    this->Exhale_Time = 0;
    this->Start_Time = 0;
}

int SysConfig::get_IE_Ratio()
{
    return this->IE_Ratio;
}

int SysConfig::get_Resp_Rate()
{
    return this->Resp_Rate;
}

int SysConfig::get_Tidal_Volume()
{
    return this->Tidal_Volume;
}

int SysConfig::get_Inh_Time()
{
    return this->Inhale_Time;
}

int SysConfig::get_Exh_Time()
{
    return this->Exhale_Time;
}

unsigned long SysConfig::get_Start_Time()
{
    return this->Start_Time;
}

void SysConfig::set_IE_Ratio(int IE_Ratio)
{
    this->IE_Ratio = IE_Ratio;
}

void SysConfig::set_Resp_Rate(int Resp_Rate)
{
    this->Resp_Rate = Resp_Rate;
    this->set_Inh_Time();
    this->set_Exh_Time();
}

void SysConfig::set_Tidal_Volume(int Tidal_Volume)
{
    this->Tidal_Volume = Tidal_Volume;
}

void SysConfig::set_Inh_Time()
{
    float num = (float)60000;
    float den = (get_Resp_Rate() * (get_IE_Ratio() + 1));
    float result = num / den;
    this->Inhale_Time = (int)result;
}

void SysConfig::set_Exh_Time()
{
    float num = (float)60000 * get_IE_Ratio();
    float den = (get_Resp_Rate() * (get_IE_Ratio() + 1));
    float result = num / den;
    this->Exhale_Time = (int)result;
}

void SysConfig::set_Start_Time()
{
    this->Start_Time = millis();
}

void SysConfig::update(SysConfig *new_config)
{
    this->set_IE_Ratio(new_config->get_IE_Ratio());
    this->set_Resp_Rate(new_config->get_Resp_Rate());
    this->set_Tidal_Volume(new_config->get_Tidal_Volume());
    this->set_Inh_Time();
    this->set_Exh_Time();
    this->Start_Time = new_config->get_Start_Time();
}
