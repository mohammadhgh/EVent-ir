#include <configuration.h>

PinConfiguration *PinConfiguration::INSTANCE = NULL;

PinConfiguration *PinConfiguration::getInstance()
{
	if (INSTANCE == NULL)
	{
		INSTANCE = new PinConfiguration();
	}
	return INSTANCE;
}

void PinConfiguration::pinConfiguration()
{
	//Dummy Input Pin
	pinMode(dummyInput, INPUT);

	// Motor pins
	pinMode(motorOut1, OUTPUT);
	digitalWrite(motorOut1, LOW);
	pinMode(motorOut2, OUTPUT);
	digitalWrite(motorOut2, LOW);
	pinMode(motorControl, OUTPUT);
	pinMode(motorDriverOnOff, OUTPUT);
	digitalWrite(motorDriverOnOff, LOW);	

	//----buttons
	pinMode(onButton_pin, INPUT);
	pinMode(applyButton_pin, INPUT);

	//----uSwitches
	pinMode(open_uSw_pin, INPUT);

	//----buzzer
	pinMode(buzzerPin, OUTPUT);
	digitalWrite(buzzerPin, LOW);

	//----LEDs
	pinMode(bLED_pin, OUTPUT);
	digitalWrite(bLED_pin, LOW);
	pinMode(wLED_pin, OUTPUT);
	digitalWrite(wLED_pin, LOW);
	pinMode(pLED1_pin, OUTPUT);
	digitalWrite(pLED1_pin, LOW);
	pinMode(pLED2_pin, OUTPUT);
	digitalWrite(pLED2_pin, LOW);			

}
