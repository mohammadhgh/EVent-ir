#include <motor_driver.h>

Motor_Driver::Motor_Driver(Motor* motor)
{
    this->local_sysconfig = SysConfig(0, 0, 0);
    this->pMotor = motor;
}

void Motor_Driver::update_sysconfig(SysConfig* newconfig)
{
    this->local_sysconfig.update(newconfig);
}

void Motor_Driver::check()
{
    int mot_Dir = 0;
    int ieRatio  = local_sysconfig.get_IE_Ratio();
    int respRate = local_sysconfig.get_Resp_Rate();
    int inhale   = 60/(respRate*(ieRatio+1));
    int exhale   = 60*ieRatio/(respRate*(ieRatio+1));
    if(pMotor->getStatus()==MOTOR_IS_ON){
        mot_Dir=pMotor->getDirection();
        


    }   
}

