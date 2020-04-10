#include <button.h>

Button::Button(int pin)
{
    this->pin = pin;
    this->hits = 0;
    this->last_hit = 0;
}

void Button::setHnadler(void (*handler_func)(void))
{
    attachInterrupt(digitalPinToInterrupt(this->pin), handler_func, LOW);
}

int Button::getValue()
{
    int return_val;
    return_val = digitalRead(this->pin);

    return return_val;
}

int Button::increment_hits()
{
    this->hits++;

    return this->hits;
}

void Button::set_last_hit(long hit_time)
{
    this->last_hit = hit_time;
}

long Button::get_last_hit()
{
    return this->last_hit; 
}
