#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H
#include <Arduino.h>
#include <HX711.h>
class PressureSensor
{
private:
    HX711 *scale;
    float PR;
    int Sck_pin;
    int Out_pin;
    float sensorDivider;
    long sensorOfset;

public:
    PressureSensor(int Out_pin, int Sck_pin);
    float Read_Pressure();
};

#endif