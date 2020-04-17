#include <motor_driver.h>

Motor_Driver::Motor_Driver(Motor* motor)
{
    this->local_sysconfig = new SysConfig(0, 0, 0);
    this->pMotor = motor;
    this->inhaleExhale = INHALE;
}

void Motor_Driver::update_sysconfig(SysConfig* newconfig)
{
    this->local_sysconfig->update(newconfig);
}

void Motor_Driver::check()
{
    unsigned long current_Time = 0;
    /*unsigned long start_Time = this->local_sysconfig->get_Start_Time();

    if(pMotor->getStatus()==MOTOR_IS_ON){
        current_Time = millis();    
        if(this->inhaleExhale == INHALE){
            pMotor->setSpeed(50);
            pMotor->setDirection(DIRECTION_CLOSE);
            if (((signed long)(current_Time - start_Time))==this->local_sysconfig->get_Inh_Time()){
                pMotor->setSpeed(25);
                pMotor->motorSwitch();
                this->local_sysconfig->set_Start_Time();
                this->inhaleExhale = EXHALE;
            }
        }
        else
        {
            if (((signed long)(current_Time - start_Time))==this->local_sysconfig->get_Exh_Time()){
                pMotor->setSpeed(50);
                pMotor->motorSwitch();
                this->local_sysconfig->set_Start_Time();
                this->inhaleExhale = INHALE;               
            }
        }*/
        


        //pMotor->setSpeed(local_sysconfig->get_Inh_Time());
    //}   
}

