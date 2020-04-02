#include <configuration.h>
#include <motor.h>

PinConfiguration *PinConfiguration::INSTANCE = NULL;

PinConfiguration *PinConfiguration::getInstance()
{
	if (INSTANCE == NULL)
	{
		INSTANCE = new PinConfiguration();
	}
	return INSTANCE;
}

void static motorKeyWrapper()
{
	if (millis() - PinConfiguration::getInstance()->motorKeyTime > PinConfiguration::debounceDelay)
	{
		PinConfiguration::getInstance()->motorKeyTime = millis();
		Motor::getInstance()->motorSwitch();
	}
}
void static directionKeyWrapper()
{
	if (millis() - PinConfiguration::getInstance()->directionKeyTime > PinConfiguration::debounceDelay)
	{
		PinConfiguration::getInstance()->directionKeyTime = millis();
		Motor::getInstance()->changeDirection();
	}
}

void PinConfiguration::pinConfiguration()
{
	// Motor pins
	pinMode(motorOut1, OUTPUT);
	digitalWrite(motorOut1, initialPolarity);
	pinMode(motorOut2, OUTPUT);
	digitalWrite(motorOut2, initialPolarity);
	pinMode(motorControl, OUTPUT);

	//knobs
	pinMode(motorSpeedKnob, INPUT);

	//buttons
	pinMode(motorKey, INPUT);
	digitalWrite(motorKey, HIGH);
	attachInterrupt(digitalPinToInterrupt(motorKey), motorKeyWrapper, FALLING);

	pinMode(directionKey, INPUT);
	digitalWrite(directionKey, HIGH);
	attachInterrupt(digitalPinToInterrupt(directionKey), directionKeyWrapper, FALLING);
}
