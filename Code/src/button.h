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
    int interruptMode;
    long btnUpTime;
    long btnDnTime;
    bool ignoreUp;
    bool clicked;
    int  on_off_Stat;
    bool interrupted;
    void (*pressCallback)(void);
    
public:
    Button(int pin, uint8_t ioMode, void (*callback_func)(void), int interruptMode);
    Button(int pin);
    void setPressCallback(void (*callback_func)(void));
    void callBackFunc();
    void enableInterrupt(void (*callback_func)(void));
    bool get_Clicked();
    int  get_Status();
    int  get_On_Off();
    bool isInterrupted();
    void set_On_Off();
    void set_Clicked(bool clicked);
    void setIsInterrupted(bool interrupted);
    void check();    
};

#endif