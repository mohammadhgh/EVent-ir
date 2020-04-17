#ifndef Potentiometer_h
#define Potentiometer_h

#include <Arduino.h>
#include <avr/wdt.h>
#include <configuration.h>
#define MAX_RANGE_SIZE 23
class Potentiometer
{
private:
    int pin;
    int subMultiple;
    int subValue;
    int table[MAX_RANGE_SIZE];

public:
    Potentiometer(int pin, int subMultiple, int subValue);
    void set_Range(int table[]);
    int Potentiometer_Read();
};

#endif