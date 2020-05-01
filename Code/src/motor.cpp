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

void Motor::changeDirection()
{
    //if(this->motorStatus==MOTOR_IS_ON){
        if(this->direction==DIRECTION_CLOSE)
            this->direction=DIRECTION_OPEN;
        else
            this->direction=DIRECTION_CLOSE;
    //}    
    this->setMotorOut();
}

float Motor::convertRMPtoPWM(float RPM){
    return (RPM_PWM_Ratio*RPM+RPM_PWM_Constant);
}

float Motor::convertOmegatoRPM(float omega, float time){
    return DEGREE_TO_RPM*omega/time;
}

void Motor::setEncPeriod(int encPeriod){
    this->encPeriod = encPeriod;
}

int Motor::getStatus()
{
    return this->motorStatus;
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

void Motor::setSpeed(float newSpeed)
{
    this->motorSpeed = convertRMPtoPWM(newSpeed);
    Serial.println(this->motorSpeed);
    analogWrite(PinConfiguration::motorControl, getSpeedPWM());
}

float Motor::getSpeed()
{
    return this->motorSpeed;
}
int Motor::getSpeedPWM()
{
    return map(round(this->motorSpeed), 0, 100, 0, 255);
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

float Motor::getEncRPM()
{
    float RPM = 0;
    int period = this->getEncPeriod();
    if(period>0){
        RPM = (long)period * (long)MOTOR_PULSE_PER_TURN * (float)4; 
        RPM = (float)60000000 / RPM;
    }
    if (RPM>150)
        RPM=this->oldRPM;
    this->oldRPM=RPM;    
    return RPM;
}

int Motor::getEncAngle()
{
    int angle = 0;
    
}
