#include <buzzer.h>

Buzzer::Buzzer(int pin)
{
    this->pin = pin;
    this->sound_freq = 1000; //active buzzer
    this->on_delay = 500;
}

void Buzzer::beep(int beeps_count)
{
    for (int i = 0; i < beeps_count; i++)
    {
        tone(this->pin, this->sound_freq, this->on_delay);
        delay(this->on_delay);
        noTone(this->pin);
        delay(this->on_delay);
    }
}