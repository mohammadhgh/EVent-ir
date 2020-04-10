#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include <configuration.h>

class Buzzer
{
private:
    static Buzzer *INSTANCE;
    int sound_freq = 10; //active buzzer
    int on_delay = 50;
    int off_delay = 500;
public:
    static Buzzer *getInstance();
    void beep(int beeps_count);
};

#endif