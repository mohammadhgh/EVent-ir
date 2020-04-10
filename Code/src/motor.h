#ifndef EVENT_MOTOR_H
#define EVENT_MOTOR_H

#include <Arduino.h>
#include <avr/wdt.h>
#include <configuration.h>

// #define INITIAL_POLARITY LOW

#define DIRECTION_CLOSE     LOW
#define DIRECTION_OPEN      HIGH

#define MOTOR_IS_ON         HIGH
#define MOTOR_IS_OFF        LOW

class Motor
{
private:
    static Motor *INSTANCE;
    int motorSpeed = 50;
    int motorStatus = MOTOR_IS_OFF;
    int direction = DIRECTION_OPEN;
public:
    static Motor *getInstance();
    int  getStatus();
    void changeDirection();
    void setDirection(int direction);
    int  getDirection();
    void setMotorOut();
    void setSpeed(int a);
    int  getSpeed();
    int  getSpeedPWM();
    void motorStop();
    void motorStart();
    void motorSwitch();
};

#endif
