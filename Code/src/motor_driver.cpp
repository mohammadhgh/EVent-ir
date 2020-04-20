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

void Motor_Driver::check()
{
    unsigned long current_Time = 0;
    unsigned long start_Time = 0;
    int respRate = local_sysconfig->get_Resp_Rate();
    if (pMotor->getStatus() == MOTOR_IS_ON)
    {


        start_Time = this->local_sysconfig->get_Start_Time();
        current_Time = millis();
        Serial.println("here");
        Serial.println(start_Time);
        Serial.println(current_Time);
        Serial.println(this->local_sysconfig->get_Inh_Time());
        if (this->inhaleExhale == INHALE)
        {
            //Serial.println(respRate);
            pMotor->setSpeed(respRate+40);
            pMotor->setDirection(DIRECTION_CLOSE);
            if (((signed long)(current_Time - start_Time)) >= this->local_sysconfig->get_Inh_Time())
            {
                pMotor->setSpeed(respRate+60);
                pMotor->setDirection(DIRECTION_OPEN);
                this->local_sysconfig->set_Start_Time();
                this->inhaleExhale = EXHALE;
            }
        }
        else
        {
            Serial.println("here0");
            if (((signed long)(current_Time - start_Time)) >= this->local_sysconfig->get_Exh_Time())
            {
                pMotor->setSpeed(respRate+40);
                pMotor->setDirection(DIRECTION_CLOSE);
                this->local_sysconfig->set_Start_Time();
                this->inhaleExhale = INHALE;
            }
        }
    }
}
