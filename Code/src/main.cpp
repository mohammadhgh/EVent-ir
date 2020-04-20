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

long testTimer = 0;

/* Global Objects */
SysConfig *Global_SysConfig;

Button *ON_button;
Button *open_uSwitch;
Button *close_uSwitch;

LED *gLED;
LED *ardLED;

Buzzer *coolBuzz;
Motor_Driver *mot_Driver;

Potentiometer *respVolume;
Potentiometer *respCycle;

int table_RV[] = {200, 300, 400, 500, 600, 700, 800};
int table_RC[23];

int RV = 0;
int RC = 0;
/* ------------- on Button CallBacks ------------*/
/*void static onButton_callback()
{

	ON_button->set_On_Off();
	if (ON_button->get_On_Off() == BSTATE_ON)
	{
		Global_SysConfig->set_Start_Time();
		mot_Driver->update_sysconfig(Global_SysConfig);
		Motor::getInstance()->motorStart();
	}
	else
	{
		Motor::getInstance()->motorStop();
	}

	Motor::getInstance()->motorSwitch();
	gLED->set_val(Motor::getInstance()->getStatus());
	coolBuzz->beep(2);
}
*/
/* ---------- uSwithches callbacks ----------------- */
/*
void static open_uSw_callback()
{
	Motor::getInstance()->setDirection(DIRECTION_CLOSE);
	open_uSwitch->set_Clicked();
}
/*
void static close_uSw_callback()
{
	Motor::getInstance()->setDirection(DIRECTION_OPEN);
}
*/
/* ------------- on Button CallBacks ------------*/
/*
void static initial_Check()
{
	if (open_uSwitch->get_Status() == BSTATE_HIGH)
	{
		Serial.print("Initial Setup");
		Motor::getInstance()->setDirection(DIRECTION_OPEN);
		Motor::getInstance()->motorStart();
		do
		{
			open_uSwitch->check();
		} while (!open_uSwitch->get_Clicked());
		Motor::getInstance()->motorStop();
	}
}
*/
void setup()
{
	Serial.begin(9600);

	Global_SysConfig = new SysConfig(2, 0, 0);
	PinConfiguration::getInstance()->pinConfiguration();

	coolBuzz = new Buzzer(PinConfiguration::buzzerPin);

	mot_Driver = new Motor_Driver(Motor::getInstance());

	ON_button = new Button(PinConfiguration::onButton_pin);
	//ON_button->setPressCallback(onButton_callback);

	open_uSwitch = new Button(PinConfiguration::open_uSw_pin);
	//open_uSwitch->setPressCallback(open_uSw_callback);

	close_uSwitch = new Button(PinConfiguration::close_uSw_pin);
	//close_uSwitch->setPressCallback(close_uSw_callback);

	gLED = new LED(PinConfiguration::gLED_pin);

	ardLED = new LED(PinConfiguration::ardLED);

	/*LCD::getInstance()->LCD_Cover();
	delay(2000);
	LCD::getInstance()->LCD_Clear();*/

	respVolume = new Potentiometer(PinConfiguration::Potentiometer_Volume, 7);
	respCycle = new Potentiometer(PinConfiguration::Potentiometer_Cycle, 23);

	for (size_t i = 8; i <= 30; i++)
	{
		table_RC[i - 8] = i;
	}

	respVolume->set_Range(table_RV, sizeof table_RV);
	respCycle->set_Range(table_RC, sizeof table_RC);

	Motor::getInstance()->motorStart();
	Global_SysConfig->set_Start_Time();
	mot_Driver->update_sysconfig(Global_SysConfig);	
	//initial_Check();
}

void loop()
{
	Global_SysConfig->set_Resp_Rate(respCycle->Potentiometer_Read());
	Serial.println(respCycle->Potentiometer_Read());
	//Motor::getInstance()->setSpeed(respCycle->Potentiometer_Read()+50);
	mot_Driver->update_sysconfig(Global_SysConfig);
	mot_Driver->check();
	//LCD::getInstance()->LCD_Menu(respVolume->Potentiometer_Read(), respCycle->Potentiometer_Read());

	//ON_button->check();
	//open_uSwitch->check();
	

	wdt_reset();
}
