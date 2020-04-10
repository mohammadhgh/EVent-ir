#include <knob.h>

Knob::Knob(int pin)
{
    this->pin = pin;
}

int Knob::getVal()
{
    int val = analogRead(this->pin);
    val = map(val, 0, 1023, 0, 100);

    return val;
}