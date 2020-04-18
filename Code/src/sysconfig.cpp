#include <sysconfig.h>

SysConfig::SysConfig(int IE_Ratio, int Resp_Rate, int Tidal_Volume)
{
    this->IE_Ratio = IE_Ratio;
    this->Resp_Rate = Resp_Rate;
    this->Tidal_Volume = Tidal_Volume;
}

int SysConfig::get_IE_Ratio()
{
    return this->IE_Ratio;
}

void SysConfig::set_IE_Ratio(int IE_Ratio)
{
    this->IE_Ratio = IE_Ratio;
}

void SysConfig::set_Resp_Rate(int Resp_Rate)
{
    this->Resp_Rate = Resp_Rate;
}

void SysConfig::set_Tidal_Volume(int Tidal_Volume)
{
    this->Tidal_Volume = Tidal_Volume;
}

void SysConfig::update(SysConfig* new_config)
{
    this->set_IE_Ratio(new_config->get_IE_Ratio());
    this->set_Resp_Rate(new_config->get_Resp_Rate());
    this->set_Tidal_Volume(new_config->get_Tidal_Volume());
}
