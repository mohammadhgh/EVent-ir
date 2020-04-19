#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>

#include <configuration.h>
#include <motor.h>
#include <sysconfig.h>

#define INHALE 0x0
#define EXHALE 0x1

class Motor_Driver
{
private:
    Motor* pMotor;
    SysConfig* local_sysconfig;
    int inhaleExhale;
public:
    Motor_Driver(Motor* motor);
    void update_sysconfig(SysConfig* newconfig);
    void set_motor();
    void check();
};

#endif
