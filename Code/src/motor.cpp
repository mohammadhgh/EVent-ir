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
    this->direction = ~this->direction;
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
    char my_string[50];
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
