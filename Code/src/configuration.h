#include <Arduino.h>

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class PinConfiguration
{
private:
    static PinConfiguration *INSTANCE;

public:
    static PinConfiguration *getInstance();

    const int initialPolarity = 0;
    const static int debounceDelay = 250;

    const static int motorOut1 = 13;
    const static int motorOut2 = 12;
    const static int motorControl = 11;

    const static int motorSpeedKnob = A0;

    const static int directionKey = 3;
    long directionKeyTime = 0;
    const static int motorKey = 2;
    long motorKeyTime = 0 ;

    void pinConfiguration();
};

#endif