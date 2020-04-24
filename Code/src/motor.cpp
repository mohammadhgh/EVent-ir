#include <motor.h>

Motor *Motor::INSTANCE = NULL;

Motor *Motor::getInstance()
{
    if (INSTANCE == NULL)
    {
        INSTANCE = new Motor();
    }
    return INSTANCE;
}

int Motor::getStatus()
{
    return this->motorStatus;
}

void Motor::changeDirection()
{
    if(this->motorStatus==MOTOR_IS_ON){
        if(this->direction==DIRECTION_CLOSE)
            this->direction=DIRECTION_OPEN;
        else
            this->direction=DIRECTION_CLOSE;
    }    
    this->setMotorOut();
}

void Motor::setDirection(int directionl)
{
    this->direction = directionl;
    this->setMotorOut();
}

int Motor::getDirection()
{
    return this->direction;
}

void Motor::setMotorOut()
{
    if (this->motorStatus == MOTOR_IS_ON)
    {
        digitalWrite(PinConfiguration::motorOut1, this->direction);
        delay(50);
        digitalWrite(PinConfiguration::motorOut2, not(this->direction));
    }
    else
    {
        digitalWrite(PinConfiguration::motorOut1, LOW);
        digitalWrite(PinConfiguration::motorOut2, LOW);
    }
}

void Motor::setSpeed(int newSpeed)
{
    this->motorSpeed = newSpeed > 100 ? 100 : newSpeed;
    analogWrite(PinConfiguration::motorControl, getSpeedPWM());
}

int Motor::getSpeed()
{
    return this->motorSpeed;
}
int Motor::getSpeedPWM()
{
    return map(this->motorSpeed, 0, 100, 0, 255);
    wdt_enable(WDTO_500MS);
}
void Motor::motorStop()
{
    this->motorStatus = MOTOR_IS_OFF;
    this->setMotorOut();
}
void Motor::motorStart()
{
    this->motorStatus = MOTOR_IS_ON;
    this->setMotorOut();
}
void Motor::motorSwitch()
{
    if (motorStatus == MOTOR_IS_ON)
    {
        motorStop();
    }
    else
    {
        motorStart();
    }
}

void Motor::encCheck()
{
    long nowTime = micros();

    if(nowTime - this->encLastCheck > this->encDebounceTime)
    {
            this->encLastCheck = nowTime;

            int nowState = digitalRead(PinConfiguration::motorEncoderPin);
            
            if(nowState==HIGH && this->encLastState==LOW)
            {
                if (nowTime - this->encLastTime > MOTOR_ENC_PERIOD_OFF)
                {
                    this->encPulseCount = 0;
                    this->encPeriod = 0;
                }
                else
                {
                    this->encPulseCount++;
                    this->encPeriod = nowTime - this->encLastTime;
                }

                this->encLastTime = nowTime;
                
            }

            this->encLastState = nowState;
    }
}

int Motor::getEncCount()
{
    return this->encPulseCount;
}

void Motor::resetEncCount()
{
    this->encPulseCount = 0;
}

int Motor::getEncPeriod()
{
    return this->encPeriod;
}

long Motor::getEncRPM()
{
    long RPM = 0;
    int period = this->getEncPeriod();
    RPM = (long)period * (long)MOTOR_PULSE_PER_TURN;
    RPM = (long)60000000 / RPM;
    if(RPM < 0)
    {
        RPM=0;
    }
    return RPM;
}

int Motor::getEncAngle()
{
    int angle = 0;
    
}
