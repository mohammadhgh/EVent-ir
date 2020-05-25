#include <button.h>

Button::Button(int pin, uint8_t ioMode, void (*callback_func)(void), int interruptMode)
{
    this->pin = pin;
    this->interruptMode = interruptMode;
    this->btnDnTime     = 0;
    this->btnUpTime     = 0;
    this->lastState     = HIGH;
    this->ignoreUp      = false;
    this->clicked       = false;
    this->on_off_Stat   = BSTATE_OFF;
    this->pressCallback = NULL;
    this->interrupted   = false;
    attachInterrupt(digitalPinToInterrupt(pin), callback_func, interruptMode);
}

Button::Button(int pin)
{
    this->pin           = pin;
    this->btnDnTime     = 0;
    this->btnUpTime     = 0;
    this->lastState     = HIGH;
    this->ignoreUp      = false;
    this->clicked       = false;
    this->on_off_Stat   = BSTATE_OFF;
    this->pressCallback = NULL;
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

void Button::set_Clicked(bool clicked){
    this->clicked = clicked;
}

bool Button::get_Clicked(){
    return this->clicked;
}

int Button::get_On_Off(){
    return this->on_off_Stat;
}

bool Button::isInterrupted(){
    return this->interrupted;
}

void Button::set_On_Off(){   
    if(this->get_On_Off()==BSTATE_ON)
        this->on_off_Stat=BSTATE_OFF;
    else    
        this->on_off_Stat=BSTATE_ON;
}

void Button::setIsInterrupted(bool interrupted){
    this->interrupted=interrupted;
}

void Button::check()
{

    // Read the state of the button
    int buttonVal = digitalRead(this->pin);

    // Test for button pressed and store the down time
    if (buttonVal == LOW && 
        this->lastState == HIGH && (millis() - this->btnUpTime) > PinConfiguration::debounceDelay)
    {
        this->btnDnTime = millis();   
        this->lastState = LOW;
        this->pressCallback();
    }

    // Test for button release and store the up time
    if (buttonVal == HIGH && 
        this->lastState == LOW && 
        (millis() - this->btnDnTime) > PinConfiguration::debounceDelay)
    {
        this->btnUpTime = millis();
        this->lastState = HIGH;
    }

    // Test for button held down for longer than the hold time
    if (buttonVal == LOW && 
        (millis() - this->btnDnTime) > PinConfiguration::holdTime)
    {
        this->btnDnTime = millis();   
    }
}


