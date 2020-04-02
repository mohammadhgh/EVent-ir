#include <Arduino.h>
#include <configuration.h>

#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
private:
    static Motor *INSTANCE;
    int motorSpeed = 50;
    int motorStatus = 0;
    int direction = PinConfiguration::getInstance()->initialPolarity;

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
