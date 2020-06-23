#ifndef Potentiometer_h
#define Potentiometer_h

#include <Arduino.h>
#include <avr/wdt.h>
#include <configuration.h>

class Potentiometer
{
private:
    int pin;
    int subMultiple;
    int volumeDisplay;
    int subValue;
    int *table;
    int lastVolumeValue;
    uint8_t size;

public:
    Potentiometer(int pin, int subMultiple);
    void set_Range(int *table, uint8_t size);
    int Potentiometer_Read();
};

#endif
