#include <button.h>

Button::Button(int pin)
{
    this->pin = pin;
    this->btnDnTime = 0;
    this->btnUpTime = 0;
    this->lastState = HIGH;
    this->ignoreUp = false;

    this->pressCallback = NULL;
}

void Button::setPressCallback(void (*callback_func)(void))
{
    this->pressCallback = callback_func;
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
    }

    // Test for button release and store the up time
    if (buttonVal == HIGH && 
        this->lastState == LOW && 
        (millis() - this->btnDnTime) > PinConfiguration::debounceDelay)
    {
        if (this->ignoreUp == false)
            this->pressCallback();
        else
            this->ignoreUp = false;
        this->btnUpTime = millis();
    }

    // Test for button held down for longer than the hold time
    if (buttonVal == LOW && 
        (millis() - this->btnDnTime) > PinConfiguration::holdTime)
    {
        // event2();
        // this->ignoreUp = true;
        this->btnDnTime = millis();   
    }
}