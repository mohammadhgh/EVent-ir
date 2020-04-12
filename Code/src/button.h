#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <configuration.h>

#define BSTATE_HIGH     HIGH
#define BSTATE_LOW      LOW

class Button
{
private:
    int pin;
    int lastState;
    long btnUpTime;
    long btnDnTime;
    bool ignoreUp;

    void (*pressCallback)(void);
public:
    Button (int pin);
    void setPressCallback(void (*callback_func)(void));
    void check();
};

#endif