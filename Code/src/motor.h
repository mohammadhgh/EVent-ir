#ifndef EVENT_MOTOR_H
#define EVENT_MOTOR_H

#include <Arduino.h>
#include <avr/wdt.h>
#include <configuration.h>

#define INITIAL_POLARITY LOW

class Motor
{
private:
    static Motor *INSTANCE;
    int motorSpeed = 50;
    int motorStatus = 0;
    int direction = INITIAL_POLARITY;
public:
    static Motor *getInstance();
    void changeDirection();
    void setSpeed(int a);
    int getSpeed();
    int getSpeedPWM();
    void motorStop();
    void motorStart();
    void motorSwitch();
};

#endif
