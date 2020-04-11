// by Amir Sk
// Apr. 5rd 2020

#include <Arduino.h>
#include <configuration.h>
#include <avr/wdt.h>

#include <motor.h>
#include <buzzer.h>
#include <knob.h>
#include <button.h>
#include <led.h>

/* Global Objects */
Knob* RR_knob;

Button* ON_button;
Button* open_uSwitch;
Button* close_uSwitch;

LED* gLED;
LED* ardLED;

/* ----------------- Push Buttons Interrupt Handlers ------------*/
void static onButton_handler()
{
	if ((millis() - ON_button->get_last_hit() > PinConfiguration::debounceDelay) && 
		ON_button->getLastState() == BSTATE_HIGH)
	{
		int readVal = ON_button->getValue();
		if(readVal==LOW)
		{
			Motor::getInstance()->motorSwitch();
      		gLED->set_val(Motor::getInstance()->getStatus());
		}
		
		ON_button->set_last_hit(millis());
	}
}

/* -----------------uSwitches Interrupt Handlers----------------- */
void static open_uSw_handler()
{
	if (millis() - open_uSwitch->get_last_hit() > PinConfiguration::debounceDelay)
	{
		int readVal = open_uSwitch->getValue();
		if(readVal==LOW)
		{
			Motor::getInstance()->setDirection(DIRECTION_CLOSE);
      		// ardLED->set_val(Motor::getInstance()->getDirection());
		}
		open_uSwitch->set_last_hit(millis());
	}
}

void static close_uSw_handler()
{
	if (millis() - close_uSwitch->get_last_hit() > PinConfiguration::debounceDelay)
	{
		int readVal = close_uSwitch->getValue();
		if(readVal==LOW)
		{
			Motor::getInstance()->setDirection(DIRECTION_OPEN);
      		// ardLED->set_val(Motor::getInstance()->getDirection());
		}
		close_uSwitch->set_last_hit(millis());
	}
}

void setup()
{
	Serial.begin(9600);
	
	PinConfiguration::getInstance()->pinConfiguration();

	Buzzer::getInstance()->beep(2);

	RR_knob = new Knob(PinConfiguration::RR_knob_pin);

	ON_button = new Button(PinConfiguration::onButton_pin);
	ON_button->setHnadler(onButton_handler);

	open_uSwitch = new Button(PinConfiguration::open_uSw_pin);
	open_uSwitch->setHnadler(open_uSw_handler);

	close_uSwitch = new Button(PinConfiguration::close_uSw_pin);
	close_uSwitch->setHnadler(close_uSw_handler);

	gLED = new LED(PinConfiguration::gLED_pin);

	ardLED = new LED(PinConfiguration::ardLED);
}

void loop()
{ 
  	int rr_knob_val = RR_knob->getVal();
  	Motor::getInstance()->setSpeed(rr_knob_val);
  	wdt_reset();
}
