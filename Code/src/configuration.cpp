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
	// Motor pins
	pinMode(motorOut1, OUTPUT);
	digitalWrite(motorOut1, LOW);
	pinMode(motorOut2, OUTPUT);
	digitalWrite(motorOut2, LOW);
	pinMode(motorControl, OUTPUT);

	//----buttons
	pinMode(onButton_pin, INPUT);
	digitalWrite(onButton_pin, HIGH);
	// attachInterrupt(digitalPinToInterrupt(onButton_pin), onButton_handler, LOW);

	//----uSwitches
	pinMode(open_uSw_pin, INPUT);
	digitalWrite(open_uSw_pin, HIGH);

	pinMode(close_uSw_pin, INPUT);
	digitalWrite(close_uSw_pin, HIGH);

	//----buzzer
	pinMode(buzzerPin, OUTPUT);
	digitalWrite(buzzerPin, HIGH);

	//----LEDs
	pinMode(gLED_pin, OUTPUT);
	digitalWrite(gLED_pin, LOW);

	//TimerTest Pin
	pinMode(timerTestPin, OUTPUT);
	digitalWrite(timerTestPin, LOW);

	Serial.println("1");
}
