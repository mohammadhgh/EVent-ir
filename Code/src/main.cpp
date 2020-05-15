// by Amir Sk , MHG, MHM, ASG
// Apr. 5rd 2020

#include <Arduino.h>
#include <configuration.h>
#include <avr/wdt.h>
#include <openGLCD.h>
#include <sysconfig.h>
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

long testTimer = 0;

/* Global Objects */
SysConfig *Global_SysConfig;

Button *ON_button;
Button *open_uSwitch;

LED *gLED;
LED *ardLED;
boolean a = false;
Buzzer *coolBuzz;
Motor_Driver *mot_Driver;

Potentiometer *respVolume;
Potentiometer *respCycle;
Potentiometer *IERatio;

PID *pid;

Trajectory *trajectory;

DegreeTracker *degreeTracker;

int table_RV[] = {200, 300, 400, 500, 600, 700, 800};
int table_RC[23];
int table_IE[] = {1, 2, 3, 4};
float calcedLeftTime[400];
float calcedLeftDegree[400];
//int MotorSpeedDesired[300];
int   MotorSpeedActual[400];
float MotorPwm[400];


int RC = 0;

volatile int encFalled = 0;

int motorSpeed = 0;
unsigned long lastMilis = 0;

int j = 0; int k = 0; 
int myCounter = 0;
volatile int timeStepValid = 0;
int startDir=0;
int currentDir=0;
int dirChanged=0;
int motorStopped=0;

int timerPinVal=LOW;
int changeDir=LOW;
int comeAndGo=0;

/* ------------- Initial Check ------------*/

void static initial_Check()
{
	if (open_uSwitch->get_Status() == BSTATE_HIGH)
	{
		Serial.println("Initial Setup");
		Motor::getInstance()->setDirection(DIRECTION_OPEN);
		Motor::getInstance()->motorStart();
		while (open_uSwitch->get_Clicked() == false)
			delay(1);
		open_uSwitch->set_Clicked(false);
		Motor::getInstance()->motorStop();
	}
}

static void resetParams(){
	Motor::getInstance()->resetEncPeriod();
	Motor::getInstance()->resetPC();
	pid->resetParams();
	degreeTracker->resetPosition();
}

static void onMotorStart()
{
	resetParams();
	Motor::getInstance()->motorStart();
	timeStepValid = 0;
	Timer4Start(round(15625 * pid->getTimeStep()) - 1);
}

static void onMotorStop()
{
	Motor::getInstance()->motorStop();
	resetParams();
	Timer4Stop();
}

static void motorSpeedCheck(){
	if(round(Motor::getInstance()->getEncRPM())>30){
		Serial.println("check");
		onMotorStop();
		comeAndGo=0;
	}
}

void setup()
{
	noInterrupts();
	
	for (size_t i = 8; i <= 30; i++)
		table_RC[i - 8] = i;

	Init_Timer1();
	Init_Timer3();
	Init_Timer4();
	Init_Timer5();

	Serial.begin(115200);

	Global_SysConfig = new SysConfig(2, 20, 0);
	Global_SysConfig->set_loopParams(0.6, 4, 5e-3);

	PinConfiguration::getInstance()->pinConfiguration();

	coolBuzz = new Buzzer(PinConfiguration::buzzerPin);

	//mot_Driver = new Motor_Driver(Motor::getInstance());

	ON_button = new Button(PinConfiguration::onButton_pin, INPUT, onButton_callback, LOW);

	open_uSwitch = new Button(PinConfiguration::open_uSw_pin, INPUT, open_uSw_callback, LOW);

	gLED = new LED(PinConfiguration::gLED_pin);

	respVolume = new Potentiometer(PinConfiguration::Potentiometer_Volume, 7);
	respCycle  = new Potentiometer(PinConfiguration::Potentiometer_Cycle, 23);
	IERatio    = new Potentiometer(PinConfiguration::Potentiometer_IE, 4);

	respCycle->set_Range(table_RC, sizeof table_RC);
	respVolume->set_Range(table_RV, sizeof table_RV);
	IERatio->set_Range(table_IE, sizeof table_IE);

	pid = new PID(3, 48, 0.025, 16);
	pid->setTimeStep(Global_SysConfig->timeStep);
	pid->setOutputRange(0, 255);

	degreeTracker = new DegreeTracker((float)35, Global_SysConfig->duration, Global_SysConfig->timeStep);

	interrupts();

	Motor::getInstance()->setSpeed(240);
	Motor::getInstance()->initEnc(PinConfiguration::motorEncoderPin, INPUT, enc_callback, RISING);
	//initial_Check();
}

void loop()
{
	//mot_Driver->update_resp_rate(Global_SysConfig);
	//mot_Driver->check();
	//LCD::getInstance()->LCD_Menu(respVolume->Potentiometer_Read(), respCycle->Potentiometer_Read(), IERatio->Potentiometer_Read());
	if(motorStopped==0)
		motorSpeedCheck();
	
	if (ON_button->get_Clicked() == true && ON_button->get_On_Off() == BSTATE_ON)
	{
		Motor::getInstance()->setDirection(DIRECTION_OPEN);
		comeAndGo=1;
		onMotorStart();
		ON_button->set_Clicked(false);
	}

	else if (ON_button->get_Clicked() == true && ON_button->get_On_Off() == BSTATE_OFF)
	{
		ON_button->set_Clicked(false);
		for (int i = 0; i < myCounter; i++)
		{
			Serial.print(i);
			Serial.print("\t");
			Serial.print(calcedLeftTime[i],3);
			Serial.print("\t");
			Serial.print(calcedLeftDegree[i],3);
			Serial.print("\t");
			Serial.print(MotorPwm[i]);
			Serial.print("\t");
			Serial.println(MotorSpeedActual[i]);
		}
		
		Serial.println(j);	
		/*Serial.println(f[0]);	
		Serial.println(t[0],3);	
		Serial.println(f[1]);	
		Serial.println(t[1],3);	
		Serial.println(f[2]);	
		Serial.println(t[2],3);*/

		j=0;	
		myCounter=0;
		onMotorStop();
		comeAndGo=0;
		Motor::getInstance()->setSpeed(240);
	}

	if (open_uSwitch->get_Clicked() == true)
	{
		TCNT5 = 0;
		Motor::getInstance()->changeDirection();
		pid->resetParams();
		open_uSwitch->set_Clicked(false);
	}

	if (Motor::getInstance()->getStatus() == MOTOR_IS_ON)	
	{		
		if (timeStepValid)
		{			
			timeStepValid = 0;	
	
			degreeTracker->updateTime();
			degreeTracker->updatePosition(Motor::getInstance()->getPC());			
			motorSpeed = pid->Calc(degreeTracker->updateDesiredRPM(), Motor::getInstance()->getEncRPM());
			Motor::getInstance()->setSpeed(motorSpeed);	

			calcedLeftTime[myCounter]    = degreeTracker->getLeftTime();
			calcedLeftDegree[myCounter]  = degreeTracker->getLeftDeltaDegree();
			MotorPwm[myCounter] 		 = motorSpeed;
			MotorSpeedActual[myCounter]  = round(Motor::getInstance()->getEncRPM());

			myCounter++;
			
			if (degreeTracker->getLeftTime()<0.04){
				motorStopped = 1;
				//f[0]=Motor::getInstance()->getPC();
				//t[0]=degreeTracker->getLeftTime();
				Motor::getInstance()->motorStop();
				j++;				
			}	
		}
	}
	else if (j==1){
		if (timeStepValid)
		{			
			timeStepValid = 0;
			
			/*if(Motor::getInstance()->getEncRPM()<2.0){
				//f[2]=Motor::getInstance()->getPC();
				//t[2]=degreeTracker->getLeftTime();
				j++;
			}*/

			degreeTracker->updateTime();
			degreeTracker->updatePosition(Motor::getInstance()->getPC());	
			degreeTracker->updateDesiredRPM();
		
			calcedLeftTime[myCounter]    = degreeTracker->getLeftTime();
			calcedLeftDegree[myCounter]  = degreeTracker->getLeftDeltaDegree();
			MotorPwm[myCounter] 		 = motorSpeed;
			MotorSpeedActual[myCounter]  = round(Motor::getInstance()->getEncRPM());

			/*if(calcedLeftDegree[myCounter]<0 && j==1){
				f[1]=Motor::getInstance()->getPC();
				t[1]=degreeTracker->getLeftTime();
				j++;
			}*/

			if(myCounter<399)
				myCounter++;
		}
	}

	if(degreeTracker->getLeftTime()<0){	
		k++;
		j=0;
		motorStopped=0;		
		Timer5Stop();		
		onMotorStop();
		changeDir=not(changeDir);
		if(changeDir){
			Motor::getInstance()->setDirection(DIRECTION_CLOSE);
			degreeTracker->updateDesiredDelatTime(1.2);
		}
		else{
			Motor::getInstance()->setDirection(DIRECTION_OPEN);
			degreeTracker->updateDesiredDelatTime(0.6);
		}
		Motor::getInstance()->setSpeed(240);
		Serial.println(k);
		delay(70);
		if(k<2)
			onMotorStart();
		else{
			k=0;
		}
					
	}
		
	wdt_reset();
}
