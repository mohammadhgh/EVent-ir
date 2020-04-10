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
    char my_string[40];
    this->direction = directionl;
    sprintf(my_string, "setting direction: %d\r\n", this->direction);
    Serial.print(my_string);
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
        sprintf(my_string ,"motor is on direction : %d\r\n", this->direction);
        Serial.print(my_string);

        // if(this->direction == DIRECTION_CLOSE)
        // {
        //     Serial.print("motor out close\r\n");
        //     digitalWrite(PinConfiguration::motorOut1, HIGH);
        //     delay(50);
        //     digitalWrite(PinConfiguration::motorOut2, LOW);
        // }
        // else
        // {
        //     Serial.print("motor out open\r\n");
        //     digitalWrite(PinConfiguration::motorOut1, LOW);
        //     delay(50);
        //     digitalWrite(PinConfiguration::motorOut2, HIGH);
        // }
    
        digitalWrite(PinConfiguration::motorOut1, this->direction);
        delay(50);
        digitalWrite(PinConfiguration::motorOut2, not(this->direction));
    }
    else
    {
        Serial.print("motor off\r\n");
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
