#ifndef KNOB_H
#define KNOB_H

#include <Arduino.h>
#include <configuration.h>

class Knob
{
private:
    int pin;
public:
    Knob (int pin);
    int getVal();
};

#endif