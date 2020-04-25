#include <button.h>
#include <callBacks.h>
#include <configuration.h>

extern Button *ON_button;
extern Button *open_uSwitch;

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
