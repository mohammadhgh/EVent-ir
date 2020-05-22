#include <button.h>
#include <motor.h>
#include <callBacks.h>
#include <configuration.h>
#include <led.h>
#include <timers.h>

extern Button *onButton;
extern Button *open_uSwitch;
extern volatile int encFalled;
extern volatile int ouSwithHitPC;
extern LED *bLED;
extern LED *wLED;

/* -------------- on button callback ----------------- */
void onButton_callback_WithInteruppt()
{
	detachInterrupt(digitalPinToInterrupt(PinConfiguration::onButton_pin));
    OCR3A   = 157;					
	TCCR3B |= (1 << WGM12)|(1<<CS10) | (1<<CS12) ;
}

void onButton_callback()
{
	//Serial.println("start0");
	onButton->set_On_Off();
	onButton->set_Clicked(true);
	wLED->switch_led();
}

/* ------------ open uSwithch callback ---------------- */
void open_uSw_callback()
{
	detachInterrupt(digitalPinToInterrupt(PinConfiguration::open_uSw_pin));	
	ouSwithHitPC=Motor::getInstance()->getPC();
	bLED->switch_led();
	OCR3A  = 157;
	TCCR3B |= (1 << WGM12)| (1<<CS10) | (1<<CS12) ;	
}

/* ------------ encoder callback ---------------- */
void enc_callback(){
	Timer5Start();	
	if(TCNT5>99){
		Motor::getInstance()->setEncPeriod(TCNT5);
		Motor::getInstance()->incrementPC();
	}
	TCNT5=0;
}
