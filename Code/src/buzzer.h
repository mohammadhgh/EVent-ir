#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include <configuration.h>

class Buzzer
{
private:
    int pin;
    int sound_freq; //active buzzer
    int on_delay;
public:
    Buzzer(int pin);
    void beep(int beeps_count);
};

#endif