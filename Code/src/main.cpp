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

int table_RV[] = {200, 300, 400, 500, 600, 700, 800};
int table_RC[23];
int table_IE[] = {1, 2, 3, 4};

int RV = 0;
int RC = 0;

volatile int encFalled=0;
volatile int encValid=0;

/* ------------- Initial Check ------------*/

void static initial_Check()
{
	if (open_uSwitch->get_Status() == BSTATE_HIGH)
	{
		Serial.println("Initial Setup");
		Motor::getInstance()->setDirection(DIRECTION_OPEN);
		Motor::getInstance()->motorStart();
		while (open_uSwitch->get_Clicked()==false)
			delay(1);	
		open_uSwitch->set_Clicked(false);	
		Motor::getInstance()->motorStop();
		Serial.println(Motor::getInstance()->convertOmegatoRPM(AMBO_TOUCH_ANGLE, 1.0)+3);
		Motor::getInstance()->setSpeed(Motor::getInstance()->convertOmegatoRPM(AMBO_TOUCH_ANGLE, 1.0)+3);
		delay(100);
		Motor::getInstance()->setDirection(DIRECTION_CLOSE);
		Motor::getInstance()->motorStart();
		delay(1000);
		Motor::getInstance()->motorStop();	
		delay(1000);
	}
}

void static onMotor_Close()
{
	Motor::getInstance()->setSpeed(5);
	Motor::getInstance()->setDirection(DIRECTION_CLOSE);
	while (open_uSwitch->get_Clicked()==false)
		delay(1);	
	open_uSwitch->set_Clicked(false);	
	Motor::getInstance()->motorStop();
}

/*
void blinking()
{
	a = ON_button->get_Status();
	if (a == 0)
	{
		gLED->set_high();
		delay(500);
		gLED->switch_led();
	}
}
*/

void setup()
{
	noInterrupts(); 

	for (size_t i = 8; i <= 30; i++)
		table_RC[i - 8] = i;		

	Init_Timer3();
	Init_Timer4();
	Init_Timer5();
	
	Serial.begin(9600);

	Global_SysConfig = new SysConfig(2, 20, 0);

	PinConfiguration::getInstance()->pinConfiguration();

	coolBuzz = new Buzzer(PinConfiguration::buzzerPin);

	mot_Driver = new Motor_Driver(Motor::getInstance());

	ON_button = new Button(PinConfiguration::onButton_pin, INPUT, onButton_callback, LOW);

	open_uSwitch = new Button(PinConfiguration::open_uSw_pin, INPUT, open_uSw_callback, LOW);

	gLED = new LED(PinConfiguration::gLED_pin);

	//ardLED = new LED(PinConfiguration::ardLED);

	/*LCD::getInstance()->LCD_Cover();
	delay(2000);
	LCD::getInstance()->LCD_Clear();*/

	respVolume = new Potentiometer(PinConfiguration::Potentiometer_Volume, 7);
	respCycle = new Potentiometer(PinConfiguration::Potentiometer_Cycle, 23);
	IERatio = new Potentiometer(PinConfiguration::Potentiometer_IE, 4);

	respCycle->set_Range(table_RC, sizeof table_RC);
	respVolume->set_Range(table_RV, sizeof table_RV);
	IERatio->set_Range(table_IE, sizeof table_IE);

	interrupts();

	Motor::getInstance()->setSpeed(4);
	//Motor::getInstance()->setDirection(DIRECTION_CLOSE);
	Motor::getInstance()->initEnc(PinConfiguration::motorEncoderPin, INPUT, enc_callback, RISING);
	initial_Check();
}
void loop()
{
	
	
	//LCD::getInstance()->LCD_Menu(respVolume->Potentiometer_Read(), respCycle->Potentiometer_Read(), IERatio->Potentiometer_Read());
	//Global_SysConfig->set_Resp_Rate(respCycle->Potentiometer_Read());
	mot_Driver->update_resp_rate(respCycle->Potentiometer_Read());
	mot_Driver->check();
	/*if(Motor::getInstance()->getDirection()==DIRECTION_CLOSE){
		Motor::getInstance()->setSpeed(Global_SysConfig->get_Inhale_RPM()+7);	
	else
		Motor::getInstance()->setSpeed(Global_SysConfig->get_Exhale_RPM()+7);
	}*/
	
	if (ON_button->get_Clicked()==true && ON_button->get_On_Off()==BSTATE_ON){
		mot_Driver->update_resp_rate(respCycle->Potentiometer_Read());
        mot_Driver->init_driver();				
		ON_button->set_Clicked(false);
	}

	else if(ON_button->get_Clicked()==true && ON_button->get_On_Off()==BSTATE_OFF){
		onMotor_Close();
		ON_button->set_Clicked(false);
	}

	/*if(open_uSwitch->get_Clicked()==true){
		Motor::getInstance()->changeDirection();
		open_uSwitch->set_Clicked(false);
	}*/

	//if(encValid==1){
		//Serial.println("pwm");
		//Serial.println(Motor::getInstance()->getSpeed());
		//Serial.println("rpm");
		//Serial.println(Motor::getInstance()->getEncRPM());
		//encValid = 0;
	//}
	//delay(500);
	wdt_reset();
}
