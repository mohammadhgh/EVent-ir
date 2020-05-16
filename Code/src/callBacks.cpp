#include <button.h>
#include <motor.h>
#include <callBacks.h>
#include <configuration.h>
#include <timers.h>

extern Button *ON_button;
extern Button *open_uSwitch;
extern volatile int encFalled;

/* -------------- on button callback ----------------- */
void onButton_callback()
{
	detachInterrupt(digitalPinToInterrupt(PinConfiguration::onButton_pin));
    OCR3A   = 781;					
	TCCR3B |= (1 << WGM12)|(1<<CS10) | (1<<CS12) ;
}

/* ------------ open uSwithch callback ---------------- */
void open_uSw_callback()
{
	detachInterrupt(digitalPinToInterrupt(PinConfiguration::open_uSw_pin));	
	OCR4A  = 781;
	TCCR4B |= (1 << WGM12)|(1<<CS10) | (1<<CS12) ;	
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
