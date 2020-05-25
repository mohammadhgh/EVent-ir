#include <timers.h>
#include <button.h>
#include <callBacks.h>

extern Button *onButton;
extern Button *open_uSwitch;
extern int timeStepValid;

void Init_Timer1(){
	TCCR1B = 0;
	TCCR1A = 0;	
	TCNT1  = 0;					// preload timer 
	TIMSK1 |= (1 << OCIE1A);	// enable timer compare interrupt	
	
}

void Init_Timer3(){
	TCCR3B = 0;
	TCCR3A = 0;	
	TCNT3  = 0;					// preload timer
	TIMSK3 |= (1 << OCIE3A);	// enable timer compare interrupt
}

void Init_Timer4(){
	TCCR4B = (TCCR4B & 0b11111000) | 0x02;
}

void Init_Timer5(){
	TCCR5B = 0;
	TCCR5A = 0;	
	TCNT5  = 0;					// preload timer
}

ISR(TIMER3_COMPA_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	TCNT3  = 0;
	TIMSK3 = 0;
	OCR3A  = 0;
	if(open_uSwitch->get_Status()==BSTATE_LOW){
		open_uSwitch->set_Clicked(true);
	}		
	OCR3B = 781*4;		
	TIMSK3 |= (1 << OCIE3B);		 
}

ISR(TIMER3_COMPB_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	TCNT3 = 0;
	if(open_uSwitch->get_Status()==BSTATE_HIGH){
		TCCR3B = 0;			
		TIMSK3 = 0;
		OCR3B  = 0;
		OCR3A  = 157;
		TIMSK3= (1 << OCIE3A);  
		open_uSwitch->enableInterrupt(open_uSw_callback);			
	}
}

ISR(TIMER1_COMPA_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	TCNT1  = 0;
	timeStepValid = 1;	 
}

void Timer1Start(int period){
	TCNT1 = 0;
	OCR1A = period;
	TCCR1B |= (1 << WGM12) | (1 << CS10) | (1 << CS12);
}

void Timer1Stop(){
	TCCR1B = 0;
	TCNT1 = 0;
}

void Timer5Start(){
	TCCR5B |= (1<<CS11) | (1<<CS10);
}

void Timer5Stop(){
	TCCR5B = 0;
	TCNT5 = 0;
}

