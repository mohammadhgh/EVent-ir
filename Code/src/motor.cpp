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

Motor::Motor(){
    for (size_t i = 0; i < RPM_AVG_N; i++)
        this->RPMs[i]=0;
}

void Motor::initEnc(int pin, uint8_t ioMode, void (*callback_func)(void), int interruptMode){
    pinMode(pin, ioMode);
    attachInterrupt(digitalPinToInterrupt(pin), callback_func, interruptMode);
}

void Motor::setEncPeriod(int encPeriod){
    this->encPeriod = encPeriod;
    this->incrementPC();
}

void Motor::incrementPC(){
    this->PC+=2;; // Why are we counting 2 times per pulse?
}

void Motor::resetPC(){
    this->PC=0;
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
    this->motorSpeed = newSpeed > 255 ? 255 : newSpeed;
    analogWrite(PinConfiguration::motorControl, newSpeed);
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
    this->oldRPM = 0;
}

float Motor::getEncRPM()
{
    float RPM = 0;
    //float tempRPM = 0;
    int period = this->getEncPeriod();
    if(period>100){
        RPM = (float)period * (float)MOTOR_PULSE_PER_TURN * (float)4; 
        RPM = (long)60000000 / RPM;
        /*RPMs[rpmIndex]=RPM;
        for (size_t i = 0; i < RPM_AVG_N; i++)
        {
            tempRPM+=this->RPMs[i];
        }        
        if (this->rpmIndex<RPM_AVG_N)
            this->rpmIndex++;
        else
            this->rpmIndex = 0;
        this->oldRPM = tempRPM;*/ 
        oldRPM = RPM;              
    }
    else
    {
        RPM=oldRPM;
        //tempRPM=this->oldRPM;
    }
          
    //return tempRPM/(float)RPM_AVG_N;
    return RPM;
}

int Motor::getPC(){
    return this->PC;
}

int Motor::getEncAngle()
{
    int angle = 0;
    
}
