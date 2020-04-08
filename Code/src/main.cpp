// by Amir Sk
// Apr. 5rd 2020

#include <Arduino.h>
#include <configuration.h>
#include <avr/wdt.h>

#include <motor.h>
#include <buzzer.h>

void setup()
{
  // put your setup code here, to run once:

  PinConfiguration::getInstance()->pinConfiguration();

  Buzzer::getInstance()->beep(2);
}

void loop()
{ 
  int knob = map(analogRead(PinConfiguration::getInstance()->motorSpeedKnob), 0, 1023, 0, 100);
  Motor::getInstance()->setSpeed(knob);
  wdt_reset();
}