// by Amir Sk
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
float calcedLeftTime[200];
float calcedLeftDegree[200];

//int MotorSpeedDesired[300];
int MotorSpeedActual[200];
float MotorPwm[200];
int TNCTVal[200];

int RC = 0;

volatile int encFalled = 0;

int motorSpeed = 0;
unsigned long lastMilis = 0;

int j = 0; int f[3]; float t[3]; 
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

static void onMotorStart()
{
	Motor::getInstance()->resetEncPeriod();
	Motor::getInstance()->resetPC();
	Motor::getInstance()->motorStart();
	pid->resetParams();
	degreeTracker->resetPosition();
	timeStepValid = 0;
	TCNT4 = 0;
	OCR4A = round(15625 * pid->getTimeStep()) - 1;
	TCCR4B |= (1 << WGM12) | (1 << CS10) | (1 << CS12);
}

static void onMotorStop()
{
	Motor::getInstance()->motorStop();
	Motor::getInstance()->resetEncPeriod();
	Motor::getInstance()->resetPC();
	pid->resetParams();
	degreeTracker->resetPosition();
	TCCR4B = 0;
	TCNT4 = 0;
}

static void onChangeDirection()
{	
	//Motor::getInstance()->setSpeed(255);
	Motor::getInstance()->changeDirection();
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

	pid = new PID(3, 48, 0.025, 10);
	pid->setTimeStep(Global_SysConfig->timeStep);
	pid->setOutputRange(0, 255);

	//trajectory = new Trajectory(Global_SysConfig->resolution, 360, 0, 0, Global_SysConfig->duration);
	//trajectory->calcTrajec();

	degreeTracker = new DegreeTracker((float)35, Global_SysConfig->duration, Global_SysConfig->timeStep);

	interrupts();

	Motor::getInstance()->setSpeed(245);
	Motor::getInstance()->initEnc(PinConfiguration::motorEncoderPin, INPUT, enc_callback, RISING);
	//initial_Check();
}

void loop()
{
	//mot_Driver->update_resp_rate(Global_SysConfig);
	//mot_Driver->check();
	//LCD::getInstance()->LCD_Menu(respVolume->Potentiometer_Read(), respCycle->Potentiometer_Read(), IERatio->Potentiometer_Read());
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
		Serial.println(f[0]);	
		Serial.println(t[0],3);	
		Serial.println(f[1]);	
		Serial.println(t[1],3);	
		Serial.println(f[2]);	
		Serial.println(t[2],3);
		/*for(int i=0; i<200; i++){
			Serial.println(TNCTVal[i]);
		}*/	
		j=0;	
		myCounter=0;
		onMotorStop();
		comeAndGo=0;
		Motor::getInstance()->setSpeed(245);
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
			
			if (degreeTracker->getLeftTime()<0.045){
				motorStopped = 1;
				f[0]=Motor::getInstance()->getPC();
				t[0]=degreeTracker->getLeftTime();
				Motor::getInstance()->motorStop();
				j++;				
			}	
		}
	}
	else if (j==1 || j==2){
		if (timeStepValid)
		{			
			timeStepValid = 0;
			
			if(Motor::getInstance()->getEncRPM()<2.0){
				f[2]=Motor::getInstance()->getPC();
				t[2]=degreeTracker->getLeftTime();
				j++;
			}
			degreeTracker->updateTime();
			degreeTracker->updatePosition(Motor::getInstance()->getPC());	
		
			calcedLeftTime[myCounter]    = degreeTracker->getLeftTime();
			calcedLeftDegree[myCounter]  = degreeTracker->getLeftDeltaDegree();
			MotorPwm[myCounter] 		 = motorSpeed;
			MotorSpeedActual[myCounter]  = round(Motor::getInstance()->getEncRPM());
			if(calcedLeftDegree[myCounter]<0 && j==1){
				f[1]=Motor::getInstance()->getPC();
				t[1]=degreeTracker->getLeftTime();
				j++;
			}
			if(myCounter<199)
				myCounter++;
		}
	}
	//if(comeAndGo==1){
		//if(TCNT5>4000){
		if(degreeTracker->getLeftTime()<0){
			timerPinVal = not(timerPinVal);
			digitalWrite(PinConfiguration::timerTestPin, timerPinVal);	
			TCCR5B = 0;
			TCNT5 = 0;
			j=0;
			myCounter=0;		
			onMotorStop();
			changeDir=not(changeDir);
			if(changeDir)
				Motor::getInstance()->setDirection(DIRECTION_CLOSE);
			else
				Motor::getInstance()->setDirection(DIRECTION_OPEN);
			Motor::getInstance()->setSpeed(245);
			delay(80);
			onMotorStart();			
		}
	//}
		
	wdt_reset();
}
