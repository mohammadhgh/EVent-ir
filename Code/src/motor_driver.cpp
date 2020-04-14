#include <motor_driver.h>

Motor_Driver::Motor_Driver(Motor* motor)
{
    this->local_sysconfig = SysConfig();
    this->pMotor = motor;
}

