#include <MotorController.h>

MotorController::MotorController(/* args */)
{
    sysConfig = new SysConfig(2, 20, 0);
    sysConfig->setParams(6e-1, TIME_STEP, MINIUM_MOTOR_SPEED_IN_PWM);

    pid = new PID(KP, KI, KD, MINIUM_MOTOR_SPEED_IN_PWM, PID_IGNORE_COUNT, PID_GAURD_COUNT);
    pid->setTimeStep(sysConfig->timeStep); // Integrate into constructor
    pid->setOutputRange(0, 255);           // Integrate into constructor

    degreeTracker = new DegreeTracker(35, sysConfig->duration, sysConfig->timeStep);
}

void MotorController::startReciporating(){
    this->reciprocateStart = true;   
}

void MotorController::stopReciporating(){
    this->reciprocateStop = true;
}

void MotorController::updatePots(int IERatio, int respCycle){
    sysConfig->set_IE_Ratio(IERatio);
    sysConfig->set_Resp_Rate(respCycle);
    inhaleTime = sysConfig->get_Inh_Time()/1000;
    exhaleTime = sysConfig->get_Exh_Time()/1000;   
}

void MotorController::motorControllerHandler()
{
    timeStepValid = 0;

    switch (controllerState)
    {
    case initialCalibration:
        initialMotorCalibrationHandler();
        break;
    case beforeReciprocating:
        if (reciprocateStart){
            reciprocateStart = false;
            controllerState = reciprocating;
        }
        break;
    case reciprocating:
        reciprocatingHandler();
        if(reciprocateStop){            
            if(reciprocatingState==openningCycleStopped){
                reciprocateStop = false; 
                onMotorStop();
                reciprocatingState=closingCycleStart;  
                controllerState = beforeReciprocating;                        
            }                        
        }
        break;

    default:
        break;
    }
}

void MotorController::initialMotorCalibrationHandler()
{

    switch (calibrationState)
    {
    case initialCalibrationStart:

        setMotorOnMinimumSpeed(DIRECTION_OPEN);
        calibrationState = initialCalibrationInProgress;
        break;

    case initialCalibrationInProgress:
        motorSpeedCheck();
        if (open_uSwitch->get_Status() == BSTATE_HIGH)
        {
            Motor::getInstance()->setSpeed(sysConfig->motorInitPWM);
        }
        else
        {
            open_uSwitch->set_Clicked(false);
            Motor::getInstance()->motorStop();
            calibrationState = initialCalibrationStopping;
        }
        break;

    case initialCalibrationStopping:
        motorSpeedCheck();
        if (lastEncoderPulseCount == Motor::getInstance()->getPC())
        {
            if (motorStopDoubleGaurd == motorStopDoubleGaurdLimit)
            {
                int motorPulseCount = Motor::getInstance()->getPC();
                positionError = ((float)motorPulseCount - (float)on_uSwithHitPC) * (float)360 / (float)MOTOR_PULSE_PER_TURN;
                calibrationState = initialCalibrationDone;
            }
            motorStopDoubleGaurd++;
        }
        else
        {
            lastEncoderPulseCount = Motor::getInstance()->getPC();
            motorStopDoubleGaurd = 0;
        }

        break;
    case initialCalibrationDone:
        lastEncoderPulseCount = 0;
        controllerState = beforeReciprocating;        
        break;

    default:
        break;
    }
}

void MotorController::reciprocatingHandler()
{
    switch (reciprocatingState)
    {
    case closingCycleStart:
        Motor::getInstance()->setDirection(DIRECTION_CLOSE);
        degreeTracker->updateDesiredDelatTime(inhaleTime);
        degreeTracker->updateDesiredDeltaDegree(desiredRotation + positionError);
        setRequiredSpeed(degreeTracker->updateDesiredRPM());
        onMotorStart();
        reciprocatingState = closingCycleinProgrees;
        break;

    case closingCycleinProgrees:
        degreeTracker->updateTime();
        degreeTracker->updatePosition(Motor::getInstance()->getPC());
        motorSpeedCheck();
        if (degreeTracker->getLeftTime() > MOTOR_STOP_TIME)
        {
            setRequiredSpeed(degreeTracker->updateDesiredRPM());
        }
        else
        {
            Motor::getInstance()->motorStop();
            onStopCommandPulseCount = Motor::getInstance()->getPC();
            reciprocatingState = closingCycleStopping;
        }

        break;

    case closingCycleStopping:
        motorSpeedCheck();
        if (lastEncoderPulseCount == Motor::getInstance()->getPC())
        {
            positionError = degreeTracker->getLeftDeltaDegree();
            reciprocatingState = closingCycleStopped;
        }
        else
        {
            degreeTracker->updateTime();
            degreeTracker->updatePosition(Motor::getInstance()->getPC());
            lastEncoderPulseCount = Motor::getInstance()->getPC();
        }
        break;

    case closingCycleStopped:
        setRequiredSpeed(MINIUM_MOTOR_SPEED_IN_RPM);
        onMotorStop();
        lastEncoderPulseCount = 0;
        delay(50);        
        reciprocatingState = openningCycleStart;
        break;

    case openningCycleStart:
        Motor::getInstance()->setDirection(DIRECTION_OPEN);
        degreeTracker->updateDesiredDelatTime(exhaleTime);
        degreeTracker->updateDesiredDeltaDegree((desiredRotation + positionError)* float(0.9));
        setRequiredSpeed(degreeTracker->updateDesiredRPM());
        onMotorStart();
        reciprocatingState = openningCycleInProgress;
        break;

    case openningCycleInProgress:
        motorSpeedCheck();
        degreeTracker->updateTime();
        degreeTracker->updatePosition(Motor::getInstance()->getPC());
        if (degreeTracker->getLeftTime() > MOTOR_STOP_TIME)
        {            
            setRequiredSpeed(degreeTracker->updateDesiredRPM());
        }
        else
        {
            setRequiredSpeed(MINIUM_MOTOR_SPEED_IN_RPM);
            onStopCommandPulseCount = Motor::getInstance()->getPC();
            reciprocatingState = openningCycleReaching_uSwitch;
        }
        break;

    case openningCycleReaching_uSwitch:
        motorSpeedCheck();
        if (open_uSwitch->get_Status() == BSTATE_HIGH)
        {
            setRequiredSpeed(MINIUM_MOTOR_SPEED_IN_RPM);
            float passedDegreeFromStop = (Motor::getInstance()->getPC()-onStopCommandPulseCount)*(float)360 / (float)MOTOR_PULSE_PER_TURN;
            if(passedDegreeFromStop>BEFORE_OUSWITCH_MAX_DEGREE){
                Motor::getInstance()->motorStop();
                reciprocatingState = openSwitchNotHit;
            }            
        }
        else
        {
            open_uSwitch->set_Clicked(false);
            Motor::getInstance()->motorStop();
            reciprocatingState = openningCycleStopping;
        }
        break;

    case openningCycleStopping:
        motorSpeedCheck();
        if (lastEncoderPulseCount == Motor::getInstance()->getPC())
        {
            if (motorStopDoubleGaurd == motorStopDoubleGaurdLimit)
            {
                int motorPulseCount = Motor::getInstance()->getPC();
                positionError = ((float)motorPulseCount - (float)on_uSwithHitPC) * (float)360 / (float)MOTOR_PULSE_PER_TURN;
                reciprocatingState = openningCycleStopped;
                onMotorStop();
            }
            motorStopDoubleGaurd++;
        }
        else
        {
            lastEncoderPulseCount = Motor::getInstance()->getPC();
            motorStopDoubleGaurd = 0;
        }
        break;

    case openningCycleStopped:
        inhaleTime = sysConfig->get_Inh_Time()/1000;
        exhaleTime = sysConfig->get_Exh_Time()/1000;
        lastEncoderPulseCount = 0;
        reciprocatingState = closingCycleStart;
        break;

    case openSwitchNotHit:
        reciprocatingState = openSwitchNotHit;
        break;  

    default:
        break;
    }
}

void MotorController::setMotorOnMinimumSpeed(bool direction)
{
    Motor::getInstance()->setDirection(direction);
    setRequiredSpeed((float)MINIUM_MOTOR_SPEED_IN_RPM);
    onMotorStart();
}

void MotorController::setRequiredSpeed(float requiredSpeed)
{
    int motorSpeed = pid->Calc((float)requiredSpeed, Motor::getInstance()->getEncRPM());
    Motor::getInstance()->setSpeed(motorSpeed);
}

void MotorController::motorSpeedCheck(){
	if(round(Motor::getInstance()->getEncRPM())>MAXIMUM_MOTOR_SPEED_IN_RPM)
	{
        reciprocatingState = openSwitchNotHit;
		onMotorStop();
		Serial.println("check");
	}
}

void MotorController::onMotorStart()
{
    resetParams();
    Motor::getInstance()->motorStart();
}

void MotorController::onMotorStop()
{
    Motor::getInstance()->motorStop();
    resetParams();
}

void MotorController::resetParams()
{
    Motor::getInstance()->resetEncPeriod();
    Motor::getInstance()->resetPC();
    pid->resetParams();
    degreeTracker->resetPosition();
    onStopCommandPulseCount = 0;
    motorStopDoubleGaurd = 0;
}