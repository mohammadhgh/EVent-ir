#ifndef TIMERS_H
#define TIMERS_H

#include <Arduino.h>
#include <avr/wdt.h>

    void Init_Timer1();
    void Init_Timer3();
    void Init_Timer4();
    void Init_Timer5();

    void Timer1Start(int period);
    void Timer1Stop();
    
    void Timer5Start();
    void Timer5Stop();

#endif
