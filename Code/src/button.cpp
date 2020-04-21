#include <button.h>

Button::Button(int pin)
{
    this->pin = pin;
    this->btnDnTime = 0;
    this->btnUpTime = 0;
    this->lastState = HIGH;
    this->ignoreUp = false;
    this->clicked = false;
    this->on_off_Stat = BSTATE_OFF;
    this->pressCallback = NULL;
}

void Button::setPressCallback(void (*callback_func)(void))
{
    this->pressCallback = callback_func;
}


int Button::get_Status()
{
     // Read the state of the button
    int buttonVal = digitalRead(this->pin);
    // Test for button pressed and store the down time
    if (buttonVal == LOW && 
        this->lastState == HIGH && (millis() - this->btnUpTime) > PinConfiguration::debounceDelay)
    {
        this->btnDnTime = millis();   
        this->lastState = LOW;
    }  

    // Test for button release and store the up time
    if (buttonVal == HIGH && 
        this->lastState == LOW && 
        (millis() - this->btnDnTime) > PinConfiguration::debounceDelay)
    {
        this->btnUpTime = millis();
        this->lastState = HIGH;
    }    

    return this->lastState;
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

void Button::check()
{

    // Read the state of the button
    int buttonVal = digitalRead(this->pin);

    // Test for button pressed and store the down time
    if (buttonVal == LOW && 
        this->lastState == HIGH && (millis() - this->btnUpTime) > PinConfiguration::debounceDelay)
    {
        Serial.print("inside low\r\n");
        this->btnDnTime = millis();   
        this->lastState = LOW;
        this->pressCallback();
    }

    // Test for button release and store the up time
    if (buttonVal == HIGH && 
        this->lastState == LOW && 
        (millis() - this->btnDnTime) > PinConfiguration::debounceDelay)
    {
        Serial.print("inside hight\r\n");
        // if (this->ignoreUp == false)
        //     // this->pressCallback();
        // else
        //     this->ignoreUp = false;
        this->btnUpTime = millis();
        this->lastState = HIGH;
    }

    // Test for button held down for longer than the hold time
    if (buttonVal == LOW && 
        (millis() - this->btnDnTime) > PinConfiguration::holdTime)
    {
        // event2();
        // this->ignoreUp = true;
        Serial.print("inside hold\r\n");
        this->btnDnTime = millis();   
    }
}