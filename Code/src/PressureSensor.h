#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H
#include <Arduino.h>
#include <HX711.h>
#include <EEPROM.h>

#define CALIBRATION_HEIGHT 10 //in centimeters

class PressureSensor
{
private:
    HX711 *HX711_inst;
    float PR;
    int Sck_pin;
    int Out_pin;
    int e2p_offset_addr;
    int e2p_scale_addr;

public:
    PressureSensor(int Out_pin, int Sck_pin, 
                   int ofst_e2p_addr, int scale_e2p_addr);
    void  Calibrate(int times = 100);
    float Read_Pressure();
};

#endif
