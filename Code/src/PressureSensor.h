#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H
#include <Arduino.h>
#include <HX711.h>
class PressureSensor
{
private:
    HX711 *HX711_inst;
    float PR;
    int Sck_pin;
    int Out_pin;
    float sensorDivider;
    long sensorOfset;

public:
    PressureSensor(int Out_pin, int Sck_pin);
    void  Calibrate(int times = 100);
    float Read_Pressure();
};

#endif
