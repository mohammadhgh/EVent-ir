#include <button.h>
#include <motor.h>
#include <callBacks.h>
#include <configuration.h>

extern Button *ON_button;
extern Button *open_uSwitch;
extern volatile int encFalled;
extern int timerPinVal;
extern int TNCTVal[200];
extern int motorStopped;
int m=0;
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

	TCCR5B |= (1<<CS11) | (1<<CS10);	
	if(TCNT5>99){
		Motor::getInstance()->setEncPeriod(TCNT5);
		Motor::getInstance()->incrementPC();
	}
	TCNT5=0;
	/*if(motorStopped==1){
		TNCTVal[m]=TCNT5;
		m++;
	}	
	if (encFalled==0){
		TCNT5=0;				
		encFalled=1;
	}
	else{	
		encFalled=0;
		Motor::getInstance()->setEncPeriod(TCNT5);
		TCNT5=0;
	}*/


}
