#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <configuration.h>

class LED
{
private:
    int pin;
    bool val;
public:
    LED (int pin);
    void switch_led();
    void set_val(int val);
    void set_high();
    void set_low();
};

#endif