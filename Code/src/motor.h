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

#define RPM_AVG_N               8
class Motor
{
private:
    static Motor *INSTANCE;
    int motorSpeed = 245;
    int motorStatus = MOTOR_IS_OFF;
    int direction = DIRECTION_OPEN;

    long  encLastTime = 0;
    long  encLastCheck = 0;
    int   encPeriod = 0;
    int   encLastState = LOW;
    int   encDebounceTime = 1;
    int   encPulseCount = 0;
    int   rpmIndex=0;
    int   PC=0; //Pulse Counter
    float oldRPM=0;
    float RPMs[RPM_AVG_N];
public:
    static Motor *getInstance();
    Motor();
    void initEnc(int pin, uint8_t ioMode, void (*callback_func)(void), int interruptMode);
    int  getStatus();
    void changeDirection();
    void setDirection(int direction);
    int  getDirection();
    void setMotorOut();
    void setSpeed(int a);
    void setEncPeriod(int encPeriod);
    void incrementPC();
    void resetPC();
    int  getSpeed();
    int  getSpeedPWM();
    void motorStop();
    void motorStart();
    void motorSwitch();
    void encCallback();
    int  getEncCount();
    void resetEncPeriod();
    void resetEncRPM();
    float getEncRPM();
    int  getEncAngle();
    int  getEncPeriod();
    int  getPC();
};

#endif
