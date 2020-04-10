#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <configuration.h>

class Button
{
private:
    int pin;
    int hits;
    long last_hit;
public:
    Button (int pin);
    void setHnadler(void (*handler_func)(void));
    int getValue();
    int increment_hits();
    void set_last_hit(long hit_time);
    long get_last_hit();
};

#endif