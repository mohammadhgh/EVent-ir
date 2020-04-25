#include <motor.h>
#include <math.h>

Motor *Motor::INSTANCE = NULL;

Motor *Motor::getInstance()
{
    if (INSTANCE == NULL)
    {
        INSTANCE = new Motor();
    }
    return INSTANCE;
}

void Motor::initEnc(int pin, uint8_t ioMode, void (*callback_func)(void), int interruptMode){
    pinMode(pin, ioMode);
    attachInterrupt(digitalPinToInterrupt(pin), callback_func, interruptMode);
}

void Motor::setEncPeriod(int encPeriod){
    this->encPeriod = encPeriod;
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
        motorStop();
    else
        motorStart();
}

int Motor::getEncPeriod(){
    return this->encPeriod;
}

int Motor::getEncCount()
{
    return this->encPulseCount;
}

void Motor::resetEncPeriod()
{
    this->encPeriod = 0;
}

long Motor::getEncRPM()
{
    float RPM = 0;
    int period = this->getEncPeriod();
    if(period>0){
        RPM = (long)period * (long)MOTOR_PULSE_PER_TURN * (float)0.5; 
        RPM = (long)60000000 / RPM;
    }
    return round(RPM);
}

int Motor::getEncAngle()
{
    int angle = 0;
    
}
