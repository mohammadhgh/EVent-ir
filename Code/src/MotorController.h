#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "PID.h"
#include "DegreeTracker.h"
#include "button.h"
#include "configuration.h"
#include "callBacks.h"
#include "motor.h"
#include "sysconfig.h"
#include <timers.h>

#define MINIUM_MOTOR_SPEED_IN_RPM 8

extern Button *open_uSwitch;
extern int on_uSwithHitPC;
extern volatile int timeStepValid;

enum ControllerStates
{
    initialCalibration,
    reciprocating
};

enum InitialCalibrationStates
{
    initialCalibrationStart,
    initialCalibrationInProgress,
    initialCalibrationStopping,
    initialCalibrationDone
};

enum ReciprocatingStates
{
    closingCycleStart,
    closingCycleinProgrees,
    closingCycleStopping,
    closingCycleStopped,
    openningCycleStart,
    openningCycleInProgress,
    openningCycleReaching_uSwitch,
    openningCycleStopping,
    openningCycleStopped

};

class MotorController
{
private:
    SysConfig *sysConfig;
    PID *pid;
    DegreeTracker *degreeTracker;

    ControllerStates controllerState = initialCalibration;
    InitialCalibrationStates calibrationState = initialCalibrationStart;
    ReciprocatingStates reciprocatingState = closingCycleStart;

    float positionError = 0;
    int lastEncoderPulseCount = 0;
    int onStopCommandPulseCount = 0;
    float desiredRotation = 25;
    float desiredRotationTime = 0.5;
    float inhaleExhaleRatio = 2;
    int motorStopDoubleGaurd = 0;
    int motorStopDoubleGaurdLimit = 10;

    void setRequiredSpeed(float requiredSpeed);
    void setMotorOnMinimumSpeed(bool direction);
    void initialMotorCalibrationHandler();
    void reciprocatingHandler();
    void MotorStart();
    void motorStopped();
    void resetParams();

public:
    MotorController(/* args */);
    void motorControllerHandler();
};

#endif

MotorController::MotorController(/* args */)
{
    sysConfig = new SysConfig(2, 20, 0);
    sysConfig->setParams(6e-1, 5e-3, 37);

    pid = new PID(2.5, 32, 25e-3, 20);
    pid->setTimeStep(sysConfig->timeStep); // Integrate into constructor
    pid->setOutputRange(0, 255);           // Integrate into constructor

    degreeTracker = new DegreeTracker((float)33, sysConfig->duration, sysConfig->timeStep);
}

void MotorController::motorControllerHandler()
{
    timeStepValid = 0;

    switch (controllerState)
    {
    case initialCalibration:
        initialMotorCalibrationHandler();
        break;
    case reciprocating:
        reciprocatingHandler();
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

        if (open_uSwitch->get_Status() == BSTATE_HIGH)
        {
            setRequiredSpeed((float)MINIUM_MOTOR_SPEED_IN_RPM);
        }
        else
        {
            open_uSwitch->set_Clicked(false);
            Motor::getInstance()->motorStop();
            calibrationState = initialCalibrationStopping;
        }
        break;

    case initialCalibrationStopping:
        if (lastEncoderPulseCount == Motor::getInstance()->getPC())
        {
            if (motorStopDoubleGaurd == motorStopDoubleGaurdLimit)
            {
                int motorPulseCount = Motor::getInstance()->getPC();
                positionError = ((float)motorPulseCount - (float)on_uSwithHitPC) * (float)360 / (float)MOTOR_PULSE_PER_TURN;
                calibrationState = initialCalibrationDone;
                // Serial.print("CALIBRATION \t");
                // Serial.println(positionError);
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
        controllerState = reciprocating;

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
        degreeTracker->updateDesiredDelatTime(desiredRotationTime);
        degreeTracker->updateDesiredDeltaDegree(desiredRotation + positionError);
        setRequiredSpeed(degreeTracker->updateDesiredRPM());
        MotorStart();
        reciprocatingState = closingCycleinProgrees;
        break;

    case closingCycleinProgrees:
        degreeTracker->updateTime();
        degreeTracker->updatePosition(Motor::getInstance()->getPC());
        if (degreeTracker->getLeftTime() > 0.005)
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
        if (lastEncoderPulseCount == Motor::getInstance()->getPC())
        {
            positionError = degreeTracker->getLeftDeltaDegree();
            reciprocatingState = closingCycleStopped;
            // Serial.print("CC \t");
            // Serial.println(positionError);
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
        motorStopped();
        reciprocatingState = openningCycleStart;
        lastEncoderPulseCount = 0;
        // delay(1000);
        break;

    case openningCycleStart:
        Motor::getInstance()->setDirection(DIRECTION_OPEN);
        degreeTracker->updateDesiredDelatTime(desiredRotationTime);
        degreeTracker->updateDesiredDeltaDegree((desiredRotation + positionError)* float(0.9));
        // Serial.println(desiredRotation + positionError);
        setRequiredSpeed(degreeTracker->updateDesiredRPM());
        MotorStart();
        reciprocatingState = openningCycleInProgress;
        break;

    case openningCycleInProgress:
        degreeTracker->updateTime();
        degreeTracker->updatePosition(Motor::getInstance()->getPC());
        if (degreeTracker->getLeftTime() > 0.02)
        {
            Serial.println("Hey");
            setRequiredSpeed(degreeTracker->updateDesiredRPM());
        }
        else
        {
            pid->resetParams();
            setRequiredSpeed(MINIUM_MOTOR_SPEED_IN_RPM);
            onStopCommandPulseCount = Motor::getInstance()->getPC();
            reciprocatingState = openningCycleReaching_uSwitch;
        }
        break;

    case openningCycleReaching_uSwitch:
        if (open_uSwitch->get_Status() == BSTATE_HIGH)
        {
            setRequiredSpeed(MINIUM_MOTOR_SPEED_IN_RPM);
        }
        else
        {
            Serial.println("Yo");
            open_uSwitch->set_Clicked(false);
            Motor::getInstance()->motorStop();
            reciprocatingState = openningCycleStopping;
        }
        break;

    case openningCycleStopping:
        if (lastEncoderPulseCount == Motor::getInstance()->getPC())
        {
            if (motorStopDoubleGaurd == motorStopDoubleGaurdLimit)
            {
                int motorPulseCount = Motor::getInstance()->getPC();
                positionError = ((float)motorPulseCount - (float)on_uSwithHitPC) * (float)360 / (float)MOTOR_PULSE_PER_TURN;
                reciprocatingState = openningCycleStopped;
                // Serial.print("OC \t");
                // Serial.println(positionError);
                motorStopped();
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
        lastEncoderPulseCount = 0;
        reciprocatingState = closingCycleStart;
        // delay(1000);

        break;

    default:
        break;
    }
}

void MotorController::setMotorOnMinimumSpeed(bool direction)
{
    Motor::getInstance()->setDirection(direction);
    setRequiredSpeed((float)MINIUM_MOTOR_SPEED_IN_RPM);
    MotorStart();
}

void MotorController::setRequiredSpeed(float requiredSpeed)
{
    int motorSpeed = pid->Calc((float)requiredSpeed, Motor::getInstance()->getEncRPM());
    Motor::getInstance()->setSpeed(motorSpeed);
}

void MotorController::MotorStart()
{
    resetParams();
    Motor::getInstance()->motorStart();
}

void MotorController::motorStopped()
{
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
