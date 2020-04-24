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
#include <string.h>
#include <Stream.h>

long testTimer = 0;

/* Global Objects */
SysConfig *Global_SysConfig;

Button *ON_button;
Button *open_uSwitch;
Button *close_uSwitch;

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

volatile int onButtonInt = 0;
volatile int openSwitchInt = 0;
volatile int timerB = 0;

/* ------------- on Button CallBacks ------------*/

void static onButton_Interrupt()
{
	detachInterrupt(digitalPinToInterrupt(PinConfiguration::onButton_pin));
    OCR3A   = 512;					
	TCCR3B |= (1 << WGM12)|(1<<CS10) | (1<<CS12) ;
	
	/*if (ON_button->get_On_Off() == BSTATE_ON)
	{		
		Motor::getInstance()->setSpeed(85);
		Motor::getInstance()->setDirection(DIRECTION_CLOSE);
		Motor::getInstance()->motorStart();
		Global_SysConfig->set_Start_Time();
		mot_Driver->update_sysconfig(Global_SysConfig);
		
	}
	else
	{
		Motor::getInstance()->setSpeed(80);
		delay(200);		
		Motor::getInstance()->setSpeed(95);
		delay(200);
        Motor::getInstance()->setDirection(DIRECTION_OPEN);
		delay(500);		
		Motor::getInstance()->motorStop();
	}*/

	/*Motor::getInstance()->motorSwitch();
	gLED->set_val(Motor::getInstance()->getStatus());
	coolBuzz->beep(2);*/
}

/* ---------- uSwithches callbacks ----------------- */

void static open_uSw_callback()
{
	detachInterrupt(digitalPinToInterrupt(PinConfiguration::open_uSw_pin));	
	OCR4A  = 512;
	TCCR4B |= (1 << WGM12)|(1<<CS10) | (1<<CS12) ;	
	Motor::getInstance()->setDirection(DIRECTION_CLOSE);
	open_uSwitch->set_Clicked(true);
}

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
	}
}

void static Init_Timer3(){
	TCCR3B = 0;
	TCCR3A = 0;	
	TCNT3  = 0;					// preload timer 65536-16MHz/256/2Hz
	TIMSK3 |= (1 << OCIE3A);	// enable timer compare interrupt
}

ISR(TIMER3_COMPA_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	TCNT3  = 0;
	TIMSK3 = 0;
	OCR3A  = 0;
	if(ON_button->get_Status()==BSTATE_LOW){
		ON_button->set_On_Off();
		ON_button->set_Clicked(true);		
	}	
	OCR3B = 1024*5;		
	TIMSK3 |= (1 << OCIE3B);		 
}

ISR(TIMER3_COMPB_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	TCNT3 = 0;
	if(ON_button->get_Status()==BSTATE_HIGH){
		TCCR3B = 0;			
		TIMSK3 = 0;
		OCR3B  = 0;
		OCR3A  = 512;
		TIMSK3= (1 << OCIE3A);  
		ON_button->enableInterrupt(onButton_Interrupt);			
	}
}

void static Init_Timer4(){
	TCCR4B = 0;
	TCCR4A = 0;	
	TCNT4  = 0;					// preload timer 65536-16MHz/256/2Hz
	TIMSK4 |= (1 << OCIE4A);	// enable timer compare interrupt
}

ISR(TIMER4_COMPA_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	TCNT4  = 0;
	TIMSK4 = 0;
	OCR4A  = 0;	
	if(open_uSwitch->get_Status()==BSTATE_LOW){
		open_uSwitch->set_Clicked(true);
	}	
	OCR4B = 1024*10;		
	TIMSK4 |= (1 << OCIE4B);		 
}

ISR(TIMER4_COMPB_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	TCNT4 = 0;
	if(open_uSwitch->get_Status()==BSTATE_HIGH){
		TCCR4B = 0;			
		TIMSK4 = 0;
		OCR4B  = 0;
		OCR4A  = 512;
		TIMSK4= (1 << OCIE4A);  	
		open_uSwitch->enableInterrupt(open_uSw_callback);		
	}
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

	for (size_t i = 8; i <= 40; i++)
		table_RC[i - 8] = i;	

	Init_Timer3();
	Init_Timer4();
	
	Serial.begin(9600);

	//Global_SysConfig = new SysConfig(2, 0, 0);
	PinConfiguration::getInstance()->pinConfiguration();


	coolBuzz = new Buzzer(PinConfiguration::buzzerPin);

	//mot_Driver = new Motor_Driver(Motor::getInstance());

	ON_button = new Button(PinConfiguration::onButton_pin, INPUT, onButton_Interrupt, LOW);

	open_uSwitch = new Button(PinConfiguration::open_uSw_pin, INPUT, open_uSw_callback, LOW);

	gLED = new LED(PinConfiguration::gLED_pin);

	//ardLED = new LED(PinConfiguration::ardLED);

	LCD::getInstance()->LCD_Cover();
	delay(2000);
	LCD::getInstance()->LCD_Clear();

	respVolume = new Potentiometer(PinConfiguration::Potentiometer_Volume, 7);
	respCycle = new Potentiometer(PinConfiguration::Potentiometer_Cycle, 23);
	IERatio = new Potentiometer(PinConfiguration::Potentiometer_IE, 4);

	for (size_t i = 8; i <= 30; i++)
	{
		table_RC[i - 8] = i;
	}

	respCycle->set_Range(table_RC, sizeof table_RC);
	respVolume->set_Range(table_RV, sizeof table_RV);
	IERatio->set_Range(table_IE, sizeof table_IE);

	interrupts();

	Motor::getInstance()->setSpeed(90);

	//initial_Check();
}
void loop()
{
	
	//Global_SysConfig->set_Resp_Rate(respCycle->Potentiometer_Read());
	//mot_Driver->update_resp_rate(Global_SysConfig);
	//ON_button->check();
	//if(ON_button->get_On_Off()==BSTATE_ON)
		//mot_Driver->check();
	//LCD::getInstance()->LCD_Menu(respVolume->Potentiometer_Read(), respCycle->Potentiometer_Read());
	//Serial.println(respCycle->Potentiometer_Read());	
	if (ON_button->get_Clicked()==true && ON_button->get_On_Off()==BSTATE_ON){
		Motor::getInstance()->motorStart();
		ON_button->set_Clicked(false);
	}
	else if(ON_button->get_Clicked()==true && ON_button->get_On_Off()==BSTATE_OFF){
		Serial.println("here");
		Motor::getInstance()->motorStop();
		ON_button->set_Clicked(false);
	}
	if(open_uSwitch->get_Clicked()==true){
		
		Motor::getInstance()->changeDirection();
		open_uSwitch->set_Clicked(false);
	}
	LCD::getInstance()->LCD_Menu(respVolume->Potentiometer_Read(), respCycle->Potentiometer_Read(), IERatio->Potentiometer_Read());

	////ON_button->check();
	//open_uSwitch->check();
	//mot_Driver->check();

	Serial.println(Motor::getInstance()->getDirection());
	Serial.println(Motor::getInstance()->getStatus());
	wdt_reset();
}
