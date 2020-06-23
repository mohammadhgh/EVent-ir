#include <led.h>

LED::LED(int pin)
{
    this->pin = pin;
    this->val = false;
}

void LED::switch_led()
{
    if(this->val==true)
        this->val=false;
    else
        this->val=true;

    digitalWrite(this->pin, (uint8_t)this->val);
}

void LED::set_val(int val)
{
    this->val = val;

    digitalWrite(this->pin, (uint8_t)this->val);
}

void LED::set_high()
{
    this->val = true;
    digitalWrite(this->pin, this->val);
}

void LED::set_low()
{
    this->val = false;
    digitalWrite(this->pin, (uint8_t)this->val);
}