#ifndef EVENT_MOTOR_H
#define EVENT_MOTOR_H

#include <Arduino.h>
#include <avr/wdt.h>
#include <configuration.h>

// #define INITIAL_POLARITY LOW

#define DIRECTION_CLOSE         LOW
#define DIRECTION_OPEN          HIGH

#define MOTOR_IS_ON             HIGH
#define MOTOR_IS_OFF            LOW

#define MOTOR_PULSE_PER_TURN    1150

#define MOTOR_ENC_PERIOD_OFF    100000

class Motor
{
private:
    static Motor *INSTANCE;
    int motorSpeed = 90;
    int motorStatus = MOTOR_IS_OFF;
    int direction = DIRECTION_OPEN;

    long encLastTime = 0;
    long encLastCheck = 0;
    int  encPeriod = 0;
    int  encLastState = LOW;
    int  encDebounceTime = 1;
    int  encPulseCount = 0;
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

    void encCheck();
    int  getEncCount();
    void resetEncCount();
    int  getEncPeriod();
    long getEncRPM();
    int  getEncAngle();
};

#endif
