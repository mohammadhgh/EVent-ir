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
#include <timers.h>
#include <callBacks.h>
#include <string.h>
#include <Stream.h>
#include <PressureSensor.h>

long testTimer = 0;

/* Global Objects */
SysConfig *Global_SysConfig;

Button *ON_button;
Button *open_uSwitch;

LED *gLED;
LED *ardLED;
boolean a = false;
Buzzer *coolBuzz;
Motor_Driver *mot_Driver;

Potentiometer *respVolume;
Potentiometer *respCycle;
Potentiometer *IERatio;
PressureSensor *PR;
int table_RV[] = {200, 300, 400, 500, 600, 700, 800};
int table_RC[33];
int table_IE[] = {1, 2, 3, 4};

// volatile int encFalled = 0;
// volatile int encValid = 0;

// void enc_callback()
// {

// 	if (encFalled == 0)
// 	{
// 		TCNT5 = 0;
// 		TCCR5B |= (1 << CS11);
// 		encFalled = 1;
// 	}
// 	else
// 	{
// 		TCCR5B = 0;
// 		encFalled = 0;
// 		Motor::getInstance()->setEncPeriod(TCNT5);
// 		encValid = 1;
// 	}
// }

/* ------------- Initial Check ------------*/

// void static initial_Check()
// {
// 	if (open_uSwitch->get_Status() == BSTATE_HIGH)
// 	{
// 		Serial.println("Initial Setup");
// 		Motor::getInstance()->setDirection(DIRECTION_OPEN);
// 		Motor::getInstance()->motorStart();
// 		while (open_uSwitch->get_Clicked() == false)
// 			delay(1);
// 		open_uSwitch->set_Clicked(false);
// 		Motor::getInstance()->motorStop();
// 	}
// }

void setup()
{

	for (size_t i = 8; i <= 40; i++)
		table_RC[i - 8] = i;

	// Init_Timer3();
	// Init_Timer4();
	// Init_Timer5();

	Serial.begin(9600);

	//Global_SysConfig = new SysConfig(2, 0, 0);
	PinConfiguration::getInstance()->pinConfiguration();

	coolBuzz = new Buzzer(PinConfiguration::buzzerPin);

	mot_Driver = new Motor_Driver(Motor::getInstance());

	ON_button = new Button(PinConfiguration::onButton_pin, INPUT, onButton_callback, LOW);

	open_uSwitch = new Button(PinConfiguration::open_uSw_pin, INPUT, open_uSw_callback, LOW);

	gLED = new LED(PinConfiguration::gLED_pin);

	ardLED = new LED(PinConfiguration::ardLED);

	//noInterrupts();
	respVolume = new Potentiometer(PinConfiguration::Potentiometer_Volume, 7);
	respCycle = new Potentiometer(PinConfiguration::Potentiometer_Cycle, 33);
	IERatio = new Potentiometer(PinConfiguration::Potentiometer_IE, 4);
	PR = new PressureSensor(PinConfiguration::PR_Out, PinConfiguration::PR_Sck);

	respCycle->set_Range(table_RC, sizeof table_RC);
	respVolume->set_Range(table_RV, sizeof table_RV);
	IERatio->set_Range(table_IE, sizeof table_IE);

	//interrupts();

	// Motor::getInstance()->setSpeed(85);
	// Motor::getInstance()->initEnc(PinConfiguration::motorEncoderPin, INPUT, enc_callback, RISING);
	//initial_Check();
	LCD::getInstance()->LCD_Logo();
}
void loop()
{
	//mot_Driver->update_resp_rate(Global_SysConfig);
	//if (ON_button->get_On_Off() == BSTATE_ON)
	//mot_Driver->check();
	Serial.println(millis());
	LCD::getInstance()->LCD_Menu(respVolume->Potentiometer_Read(), respCycle->Potentiometer_Read(), IERatio->Potentiometer_Read(), PR->Read_Pressure());
	Serial.println(millis());

	//LCD::getInstance()->LCD_graph();

	// Motor::getInstance()->setSpeed(30 - respCycle->Potentiometer_Read());
	// if (ON_button->get_Clicked() == true && ON_button->get_On_Off() == BSTATE_ON)
	// {
	// 	Motor::getInstance()->motorStart();
	// 	Motor::getInstance()->resetEncPeriod();
	// 	ON_button->set_Clicked(false);
	// }
	// else if (ON_button->get_Clicked() == true && ON_button->get_On_Off() == BSTATE_OFF)
	// {
	// 	Motor::getInstance()->setSpeed(95);
	// 	delay(500);
	// 	Motor::getInstance()->motorStop();
	// 	ON_button->set_Clicked(false);
	// }
	// if (open_uSwitch->get_Clicked() == true)
	// {
	// 	Motor::getInstance()->changeDirection();
	// 	open_uSwitch->set_Clicked(false);
	// }

	// if (encValid == 1)
	// {
	// 	Serial.println(Motor::getInstance()->getEncRPM());
	// 	encValid = 0;
	// }
	// delay(100);

	// wdt_reset();
}
