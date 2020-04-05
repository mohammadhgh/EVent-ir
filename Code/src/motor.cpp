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

void Motor::changeDirection()
{
    this->direction = ~this->direction;
    if (motorStatus == 1)
    {
        digitalWrite(PinConfiguration::motorOut1, direction);
        delay(50);
        digitalWrite(PinConfiguration::motorOut2, ~direction);
    }
    else
    {
        digitalWrite(PinConfiguration::motorOut1, direction);
        digitalWrite(PinConfiguration::motorOut2, direction);
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
    if (this->motorStatus == 1)
    {
        this->motorStatus = 0;
        digitalWrite(PinConfiguration::motorOut2, this->direction);
    }
}
void Motor::motorStart()
{
    if (this->motorStatus == 0)
    {
        this->motorStatus = 1;
        analogWrite(PinConfiguration::motorControl, getSpeedPWM());
        digitalWrite(PinConfiguration::motorOut2, ~direction);
    }
}
void Motor::motorSwitch()
{
    if (motorStatus == 1)
    {
        motorStop();
    }
    else
    {
        motorStart();
    }
}
