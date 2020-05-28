#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <configuration.h>
#include <avr/wdt.h>
#include <openGLCD.h>
#include "sysconfig.h"
#include <motor.h>
#include <motor_driver.h>
#include <buzzer.h>
#include <button.h>
#include <led.h>
#include <Potentiometer.h>
#include <LCD.h>
#include <timers.h>
#include <callBacks.h>
#include <PID.h>
#include <trajectory.h>
#include <string.h>
#include <Stream.h>
#include <math.h>
#include "DegreeTracker.h"
#include "MotorController.h"

/* Global Objects */
SysConfig *Global_SysConfig;

Button *onButton;
Button *open_uSwitch;

LED *bLED;
LED *wLED;
LED *ardLED;

Buzzer *coolBuzz;

Potentiometer *respVolume;
Potentiometer *respCycle;
Potentiometer *IERatio;

PressureSensor *PR;

MotorController *motorController;

int table_RV[] = {200, 300, 400, 500, 600, 700, 800};
int table_RC[23];
int table_IE[] = {1, 2, 3, 4};

volatile int timeStepValid = 0;

float calcedLeftTime[400];
float calcedLeftDegree[400];
int   MotorSpeedActual[400];
float MotorPwm[400];

int on_uSwithHitPC = 0;
int stopPC = 0;

#endif
