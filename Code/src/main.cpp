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
	Motor::getInstance()->motorSwitch();
	gLED->set_val(Motor::getInstance()->getStatus());
	coolBuzz->beep(2);
}

/* ---------- uSwithches callbacks ----------------- */
void static open_uSw_callback()
{
	Motor::getInstance()->setDirection(DIRECTION_CLOSE);
}

void static close_uSw_callback()
{
	Motor::getInstance()->setDirection(DIRECTION_OPEN);
}

void setup()
{
	Serial.begin(9600);
	
	PinConfiguration::getInstance()->pinConfiguration();

	Global_SysConfig = new SysConfig(0, 0, 0);

	coolBuzz = new Buzzer(PinConfiguration::buzzerPin);

	RR_knob = new Knob(PinConfiguration::RR_knob_pin);

	ON_button = new Button(PinConfiguration::onButton_pin);
	ON_button->setPressCallback(onButton_callback);

	open_uSwitch = new Button(PinConfiguration::open_uSw_pin);
	open_uSwitch->setPressCallback(open_uSw_callback);

	close_uSwitch = new Button(PinConfiguration::close_uSw_pin);
	close_uSwitch->setPressCallback(close_uSw_callback);

	gLED = new LED(PinConfiguration::gLED_pin);

	ardLED = new LED(PinConfiguration::ardLED);

	resp_Vol = new Volume();
	
	mot_Driver = new Motor_Driver(Motor::getInstance());
}

void loop()
{ 
	ON_button->check();
	open_uSwitch->check();
	close_uSwitch->check();
	Global_SysConfig->set_Resp_Rate(resp_Vol->check());
	mot_Driver->update_sysconfig(Global_SysConfig);
	mot_Driver->check();

  	int rr_knob_val = RR_knob->getVal();
  	Motor::getInstance()->setSpeed(rr_knob_val);
  	wdt_reset();
}
