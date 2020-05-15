#ifndef TIMERS_H
#define TIMERS_H

#include <Arduino.h>
#include <avr/wdt.h>

    void Init_Timer1();
    void Init_Timer3();
    void Init_Timer4();
    void Init_Timer5();

    void Timer4Start(int period);
    void Timer4Stop();
    
    void Timer5Start();
    void Timer5Stop();

#endif
