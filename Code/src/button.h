#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <configuration.h>

#define BSTATE_HIGH     HIGH
#define BSTATE_LOW      LOW

#define BSTATE_ON       HIGH
#define BSTATE_OFF      LOW

class Button
{
private:
    int pin;
    int lastState;
    long btnUpTime;
    long btnDnTime;
    bool ignoreUp;
    bool clicked;
    int  on_off_Stat;
    void (*pressCallback)(void);
public:
    Button (int pin);
    void setPressCallback(void (*callback_func)(void));
    void check();
    bool get_Clicked();
    int  get_Status();
    int  get_On_Off();
    void set_On_Off();
    void set_Clicked();
};

#endif