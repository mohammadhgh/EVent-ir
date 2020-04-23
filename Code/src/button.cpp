#include <button.h>

Button::Button(int pin, uint8_t ioMode, void (*callback_func)(void), int interruptMode)
{
    this->pin = pin;
    this->interruptMode = interruptMode;
    this->btnDnTime = 0;
    this->btnUpTime = 0;
    this->lastState = HIGH;
    this->ignoreUp = false;
    this->clicked = false;
    this->on_off_Stat = BSTATE_OFF;
    this->pressCallback = NULL;
    pinMode(pin, ioMode);
    attachInterrupt(digitalPinToInterrupt(pin), callback_func, interruptMode);
}

void Button::callBackFunc(){
    set_On_Off();
}

void Button::setPressCallback(void (*callback_func)(void))
{
    this->pressCallback = callback_func;
}

void Button::enableInterrupt(void (*callback_func)(void)){
    attachInterrupt(digitalPinToInterrupt(pin), callback_func, this->interruptMode);   
}

int Button::get_Status()
{
    return digitalRead(this->pin);
}

void Button::set_Clicked(){
    this->clicked = true;
}

bool Button::get_Clicked(){
    return this->clicked;
}

int Button::get_On_Off(){
    return this->on_off_Stat;
}

void Button::set_On_Off(){   
    if(this->get_On_Off()==BSTATE_ON)
        this->on_off_Stat=BSTATE_OFF;
    else    
        this->on_off_Stat=BSTATE_ON;
}
