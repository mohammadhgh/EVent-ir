#include <motor_driver.h>

Motor_Driver::Motor_Driver(Motor *motor)
{
    this->local_sysconfig = new SysConfig(0, 0, 0);
    this->pMotor = motor;
    this->inhaleExhale = INHALE;
}

void Motor_Driver::update_sysconfig(SysConfig *newconfig)
{
    this->local_sysconfig->update(newconfig);
}

void Motor_Driver::update_resp_rate(SysConfig *newconfig)
{
    this->local_sysconfig->set_Resp_Rate(newconfig->get_Resp_Rate());
}


void Motor_Driver::check()
{
    unsigned long current_Time = 0;
    unsigned long start_Time = 0;
    int respRate = local_sysconfig->get_Resp_Rate();
    start_Time = this->local_sysconfig->get_Start_Time();
    current_Time = millis();
    if (pMotor->getStatus() == MOTOR_IS_ON)
    {      

        if (this->inhaleExhale == INHALE)
        {
            /*Serial.println("start time in inhale");
            Serial.println(start_Time);
            Serial.println(current_Time);
            Serial.println("inhale time");
            Serial.println(this->local_sysconfig->get_Inh_Time());*/          
            if (((signed long)(current_Time - start_Time)) >= this->local_sysconfig->get_Inh_Time())
            {
                pMotor->setSpeed(85);
                delay(200);
                pMotor->setDirection(DIRECTION_OPEN);
                pMotor->setSpeed(88-respRate);
                delay(100);               
                this->local_sysconfig->set_Start_Time();
                this->inhaleExhale = EXHALE;
            }
        }
        else
        {
            /*Serial.println("start time in exhale");
            Serial.println(start_Time);
            Serial.println(current_Time);*/
            if (((signed long)(current_Time - start_Time)) >= this->local_sysconfig->get_Exh_Time())
            {
                /*Serial.println("cond true");*/
                pMotor->setSpeed(85);
                delay(200);
                pMotor->setDirection(DIRECTION_CLOSE);
                pMotor->setSpeed(88-respRate);
                delay(100);
                pMotor->setSpeed(78-respRate);
                delay(100);                 
                this->local_sysconfig->set_Start_Time();
                this->inhaleExhale = INHALE;
            }
        }
    }
}
