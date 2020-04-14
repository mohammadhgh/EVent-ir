// by Amir Sk
// Apr. 5rd 2020

#include <Arduino.h>
#include <configuration.h>
#include <avr/wdt.h>

#include <sysconfig.h>
#include <motor.h>
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

/* ----------------- Push Buttons Interrupt Handlers ------------*/
void static onButton_callback()
{
	Motor::getInstance()->motorSwitch();
	gLED->set_val(Motor::getInstance()->getStatus());
	coolBuzz->beep(2);
}

/* ----------	Serial.print("inside callback\r\n");-------uSwSerial.print("inside check\r\n");itches Interrupt Handlers----------------- */
void static open_uSw_callback()
{
	Motor::getInstance()->setDirection(DIRECTION_CLOSE);
    // ardLED->set_val(Motor::getInstance()->getDirection());
}

void static close_uSw_callback()
{
	Motor::getInstance()->setDirection(DIRECTION_OPEN);
    // ardLED->set_val(Motor::getInstance()->getDirection());
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
}

void loop()
{ 
	ON_button->check();
	open_uSwitch->check();
	close_uSwitch->check();

  	int rr_knob_val = RR_knob->getVal();
  	Motor::getInstance()->setSpeed(rr_knob_val);
  	wdt_reset();
}
