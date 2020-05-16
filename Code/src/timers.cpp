#include <timers.h>
#include <button.h>
#include <callBacks.h>

extern Button *ON_button;
extern Button *open_uSwitch;
extern int timeStepValid;

void Init_Timer1(){
	TCCR1B = (TCCR1B & 0b11111000) | 0x02;
}

void Init_Timer3(){
	TCCR3B = 0;
	TCCR3A = 0;	
	TCNT3  = 0;					// preload timer
	TIMSK3 |= (1 << OCIE3A);	// enable timer compare interrupt
}

void Init_Timer4(){
	TCCR4B = 0;
	TCCR4A = 0;	
	TCNT4  = 0;					// preload timer 
	TIMSK4 |= (1 << OCIE4A);	// enable timer compare interrupt
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
	if(ON_button->get_Status()==BSTATE_LOW){
		ON_button->set_On_Off();
		ON_button->set_Clicked(true);		
	}	
	OCR3B = 1562*2;		
	TIMSK3 |= (1 << OCIE3B);		 
}

ISR(TIMER3_COMPB_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	TCNT3 = 0;
	if(ON_button->get_Status()==BSTATE_HIGH){
		TCCR3B = 0;			
		TIMSK3 = 0;
		OCR3B  = 0;
		OCR3A  = 781;
		TIMSK3= (1 << OCIE3A);  
		ON_button->enableInterrupt(onButton_callback);			
	}
}

ISR(TIMER4_COMPA_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	// Amir: PID Loop Timer, Prescaler(1024) and Interrupt are set to activate the function every 5ms.
	TCNT4  = 0;
	//timeStepValid = 1;

	TIMSK4 = 0;
	OCR4A  = 0;	
	if(open_uSwitch->get_Status()==BSTATE_LOW){
		open_uSwitch->set_Clicked(true);
	}	
	OCR4B = 1562*2;		
	TIMSK4 |= (1 << OCIE4B);		 
}


ISR(TIMER4_COMPB_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	TCNT4 = 0;
	if(open_uSwitch->get_Status()==BSTATE_HIGH){
		TCCR4B = 0;			
		TIMSK4 = 0;
		OCR4B  = 0;
		OCR4A  = 781;
		TIMSK4= (1 << OCIE4A);  	
		open_uSwitch->enableInterrupt(open_uSw_callback);		
	}
}

void Timer4Start(int period){
	TCNT4 = 0;
	OCR4A = period;
	TCCR4B |= (1 << WGM12) | (1 << CS10) | (1 << CS12);
}

void Timer4Stop(){
	TCCR4B = 0;
	TCNT4 = 0;
}

void Timer5Start(){
	TCCR5B |= (1<<CS11) | (1<<CS10);
}

void Timer5Stop(){
	TCCR5B = 0;
	TCNT5 = 0;
}

