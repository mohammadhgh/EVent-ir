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

#define RPM_PWM_Ratio           (float)-0.7626
#define RPM_PWM_Constant        (float)94.931
#define DEGREE_TO_RPM           (float)0.166667

class Motor
{
private:
    static Motor *INSTANCE;
    float motorSpeed = 80;
    int motorStatus = MOTOR_IS_OFF;
    int direction = DIRECTION_OPEN;

    long encLastTime = 0;
    long encLastCheck = 0;
    int  encLastPeriod = 0;
    int  encPeriod = 0;
    int  encLastState = LOW;
    int  encDebounceTime = 1;
    int  encPulseCount = 0;
public:
    static Motor *getInstance();
    void initEnc(int pin, uint8_t ioMode, void (*callback_func)(void), int interruptMode);
    int  getStatus();
    void changeDirection();
    float convertOmegatoRPM(float omega, float time);
    float convertRMPtoPWM(float RPM);
    void setDirection(int direction);
    int  getDirection();
    void setMotorOut();
    void setSpeed(float newSpeed);
    void setEncPeriod(int encPeriod);
    float getSpeed();
    int  getSpeedPWM();
    void motorStop();
    void motorStart();
    void motorSwitch();
    void encCallback();
    int  getEncCount();
    void resetEncPeriod();
    float getEncRPM();
    int  getEncAngle();
    int  getEncPeriod();
};

#endif
