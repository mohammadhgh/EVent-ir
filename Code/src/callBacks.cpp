#include <button.h>
#include <motor.h>
#include <callBacks.h>
#include <configuration.h>

extern Button *ON_button;
extern Button *open_uSwitch;
extern volatile int encFalled;
extern volatile int encValid;

/* -------------- on button callback ----------------- */
void onButton_callback()
{
	detachInterrupt(digitalPinToInterrupt(PinConfiguration::onButton_pin));
    OCR3A   = 512;					
	TCCR3B |= (1 << WGM12)|(1<<CS10) | (1<<CS12) ;
}

/* ------------ open uSwithch callback ---------------- */
void open_uSw_callback()
{
	detachInterrupt(digitalPinToInterrupt(PinConfiguration::open_uSw_pin));	
	OCR4A  = 512;
	TCCR4B |= (1 << WGM12)|(1<<CS10) | (1<<CS12) ;	
	open_uSwitch->set_Clicked(true);
}

/* ------------ encoder callback ---------------- */
void enc_callback(){
	if (encFalled==0){
		TCNT5=0;
		TCCR5B |= (1<<CS11) | (1<<CS10);			
		encFalled=1;
	}
	else{
		TCCR5B = 0;
		encFalled=0;
		Motor::getInstance()->setEncPeriod(TCNT5);
		encValid = 1;
	}
}
