#ifndef EVENT_CONFIGURATION_H
#define EVENT_CONFIGURATION_H

#include <motor.h>
#include <Arduino.h>


class PinConfiguration
{
private:
    static PinConfiguration *INSTANCE;

public:
    static PinConfiguration *getInstance();

    const static int debounceDelay = 250;

    const static int motorOut1 = 13;
    const static int motorOut2 = 12;
    const static int motorControl = 11;

    const static int motorSpeedKnob = A0;

    const static int directionKey = 3;
    long directionKeyTime = 0;
    const static int motorKey = 2;
    long motorKeyTime = 0;

    //----buzzer
    const static int buzzerPin = 5; //PWM

    void pinConfiguration();
};

#endif