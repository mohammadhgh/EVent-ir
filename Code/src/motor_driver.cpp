#include <motor_driver.h>

Motor_Driver::Motor_Driver(Motor *motor)
{
    this->local_sysconfig = new SysConfig(2, 0, 0);
    this->pMotor = motor;
    this->inhaleExhale = INHALE;
}

void Motor_Driver::update_sysconfig(SysConfig *newconfig)
{
    this->local_sysconfig->update(newconfig);
}

void Motor_Driver::update_resp_rate(int Resp_Rate)
{
    this->local_sysconfig->set_Resp_Rate(Resp_Rate);
}

void Motor_Driver::update_start_time()
{
    this->local_sysconfig->set_Start_Time();
}

void Motor_Driver::init_driver()
{
    pMotor->setSpeed(this->local_sysconfig->get_Inhale_RPM());
    pMotor->setDirection(DIRECTION_CLOSE);	
    pMotor->resetEncPeriod();
    update_start_time();  
	pMotor->motorStart();	    	
	  
}

void Motor_Driver::check()
{
    unsigned long current_Time = 0;
    unsigned long start_Time = 0;
    start_Time   = this->local_sysconfig->get_Start_Time();
    current_Time = millis();

    if (pMotor->getStatus() == MOTOR_IS_ON)
    {      
        if (this->inhaleExhale == INHALE)
        {                             
            if ((float)(current_Time - start_Time)/(float)1000 >= this->local_sysconfig->get_Inh_Time())
            {
                pMotor->setSpeed(local_sysconfig->get_Exhale_RPM());
                pMotor->setDirection(DIRECTION_OPEN);             
                this->local_sysconfig->set_Start_Time();
                this->inhaleExhale = EXHALE;
            }
        }
        else
        {
            if ((float)(current_Time - start_Time)/(float)1000 >= this->local_sysconfig->get_Exh_Time())
            {
                pMotor->setSpeed(local_sysconfig->get_Inhale_RPM());
                pMotor->setDirection(DIRECTION_CLOSE);                
                this->local_sysconfig->set_Start_Time();
                this->inhaleExhale = INHALE;
            }
        }
    }
}
