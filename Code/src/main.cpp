// by Amir Sk
// Apr. 5rd 2020

#include <Arduino.h>
#include <configuration.h>
#include <avr/wdt.h>

#include <sysconfig.h>
#include <motor.h>
#include <motor_driver.h>
#include <buzzer.h>
#include <knob.h>
#include <button.h>
#include <led.h>

/* Global Objects */
SysConfig* Global_SysConfig;

Knob* RR_knob;

Button* ON_button;
Button* open_uSwitch;
Button* close_uSwitch;

LED* gLED;
LED* ardLED;

Buzzer* coolBuzz;
Motor_Driver* mot_Driver;
/* ------------- on Button CallBacks ------------*/
void static onButton_callback()
{
	
	ON_button->set_On_Off();
	if (ON_button->get_On_Off()==BSTATE_ON)
	{
		//Global_SysConfig->set_Start_Time();
		//mot_Driver->update_sysconfig(Global_SysConfig);
		Motor::getInstance()->motorStart();	
	}
	else
	{
		Motor::getInstance()->motorStop();
	}
	
	/*Motor::getInstance()->motorSwitch();	
	gLED->set_val(Motor::getInstance()->getStatus());
	coolBuzz->beep(2);*/
}

/* ---------- uSwithches callbacks ----------------- */
void static open_uSw_callback()
{
	Motor::getInstance()->setDirection(DIRECTION_CLOSE);
	open_uSwitch->set_Clicked();
}

void static close_uSw_callback()
{
	Motor::getInstance()->setDirection(DIRECTION_OPEN);
}

void setup()
{
	Serial.begin(9600);
	
	PinConfiguration::getInstance()->pinConfiguration();

	Global_SysConfig = new SysConfig(2, 20, 0);

	coolBuzz = new Buzzer(PinConfiguration::buzzerPin);

	RR_knob = new Knob(PinConfiguration::RR_knob_pin);

	mot_Driver = new Motor_Driver(Motor::getInstance());

	ON_button = new Button(PinConfiguration::onButton_pin);
	ON_button->setPressCallback(onButton_callback);

	open_uSwitch = new Button(PinConfiguration::open_uSw_pin);
	open_uSwitch->setPressCallback(open_uSw_callback);

	close_uSwitch = new Button(PinConfiguration::close_uSw_pin);
	close_uSwitch->setPressCallback(close_uSw_callback);

	gLED = new LED(PinConfiguration::gLED_pin);

	ardLED = new LED(PinConfiguration::ardLED);

	//resp_Vol = new Volume();
	
	

	if(open_uSwitch->get_Status()==BSTATE_HIGH){
		Serial.print("Initial Setup");
		Motor::getInstance()->setDirection(DIRECTION_OPEN);	
		Motor::getInstance()->motorStart();
		do{
			open_uSwitch->check();
		}
		while(!open_uSwitch->get_Clicked());
		Motor::getInstance()->motorStop();	
	}

}

void loop()
{ 
	ON_button->check();
	open_uSwitch->check();
	close_uSwitch->check();
	//Global_SysConfig->set_Resp_Rate(resp_Vol->check());
	
	mot_Driver->check();

  	//int rr_knob_val = RR_knob->getVal();
  	//Motor::getInstance()->setSpeed(rr_knob_val);
  	wdt_reset();
}
