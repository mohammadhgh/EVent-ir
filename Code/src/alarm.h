#ifndef ALARM_H
#define ALARM_H

#include "Arduino.h"
#include "buzzer.h"
#include "led.h"

class ALARM
{
private:
    Buzzer *buzz;
    LED *led;

public:
    ALARM();
    void alarm(int level);
};

#endif