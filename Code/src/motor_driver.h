#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>

#include <configuration.h>
#include <motor.h>
#include <sysconfig.h>


class Motor_Driver
{
private:
    Motor* pMotor;
    SysConfig local_sysconfig;
public:
    Motor_Driver(Motor* motor);
};

#endif
