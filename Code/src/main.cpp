// by Amir Sk
// Apr. 5rd 2020

#include <Arduino.h>
#include <configuration.h>
#include <motor.h>
 #include <avr/wdt.h>

void setup()
{
  // put your setup code here, to run once:

  PinConfiguration::getInstance()->pinConfiguration();
}

void loop()
{
  int knob = map(analogRead(PinConfiguration::getInstance()->motorSpeedKnob), 0, 1023, 0, 100);
  Motor::getInstance()->setSpeed(knob);
  wdt_reset();
}