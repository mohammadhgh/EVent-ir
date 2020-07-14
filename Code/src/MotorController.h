#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "PID.h"
#include "DegreeTracker.h"
#include "button.h"
#include "configuration.h"
#include "callBacks.h"
#include "motor.h"
#include "CurveFit.h"
#include "sysconfig.h"
#include <timers.h>

#define MAXIMUM_MOTOR_SPEED_IN_RPM  40
#define MINIUM_MOTOR_SPEED_IN_RPM   6
#define MINIUM_MOTOR_SPEED_IN_PWM   12
#define TIME_STEP                   5e-3
#define DESIRED_ROTATION            29
#define EXHALE_DEGREE_RATIO         1
#define BEFORE_OUSWITCH_MAX_DEGREE  28
#define MOTOR_STOP_TIME             20e-3
#define MOTOR_STOP_TIME_OPEN_CYCLE  0.6
#define OPENING_CYCLE_TIME          0.8
#define INHALE_TO_EXHALE_PAUSE_TIME 0.15

extern Button *open_uSwitch;
extern int on_uSwithHitPC;
extern volatile int timeStepValid;

extern float calcedLeftTime[420];
extern float calcedLeftDegree[420];
extern int   MotorSpeedActual[420];
extern float MotorPwm[420];

enum ControllerStates
{
    initialCalibration,
    beforeReciprocating,
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
    openningCycleStopped,
    openSwitchNotHit

};

class MotorController
{
private:
    SysConfig *sysConfig;
    CurveFit *curveFit;
    DegreeTracker *degreeTracker;

    ControllerStates controllerState = initialCalibration;
    InitialCalibrationStates calibrationState = initialCalibrationStart;
    ReciprocatingStates reciprocatingState = closingCycleStart;

    float positionError             = 0;
    int   lastEncoderPulseCount     = 0;
    int   onStopCommandPulseCount   = 0;
    float desiredRotation           = 0;
    float desiredRotationTime       = 0.7;
    float inhaleExhaleRatio         = 2;
    int   motorPWM                  = 0;
    int   motorStopDoubleGaurd      = 0;
    int   motorStopDoubleGaurdLimit = 4;
    bool  reciprocateStart          = false;
    bool  reciprocateStop           = false;
    bool  openingCycleFinished      = false;
    int   ieRatio                   = 0;
    int   tidalVolume               = 0;
    int   respRate                  = 0;
    float inhaleTime                = 0;
    float exhaleTime                = 0;
    float leftTime                  = 0;
    int   logCounter=0;
    float curveFitRatios[3]         = {6.551, 0.7125, 0.0063};
    float pwm                       = 0;
    bool  inhaling                  = true;
    int   mtrSpdOfstTDV300[4]       = {5, 9, 12, 17};
    int   mtrMinSpdOfstTDV300[4]    = {4, 3, 4, 3};
    int   mtrSpdOfstTDV700[4]       = {0, 0, 3, 5};
    int   mtrMinSpdOfstTDV700[4]    = {2, 2, 3, 3}; 
    void setRequiredSpeed(float requiredSpeed);
    void setMotorOnMinimumSpeed(bool direction);
    void initialMotorCalibrationHandler();
    void reciprocatingHandler();
    void logMotor();
    void printLog();
    void motorSpeedCheck();
    void onMotorStart();
    void onMotorStop();
    void motorGoToPosition(float deltaTime, float deltaDegree);
    void resetParams();

public:
    MotorController(/* args */);
    void updatePots(int IERatio, int respCycle, int respVolume);
    void motorControllerHandler();
    void startReciporating();
    void stopReciporating();
};

#endif


