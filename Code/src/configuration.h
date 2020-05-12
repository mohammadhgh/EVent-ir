#ifndef EVENT_CONFIGURATION_H
#define EVENT_CONFIGURATION_H

#include <Arduino.h>

class PinConfiguration
{
private:
    static PinConfiguration *INSTANCE;

public:
    static PinConfiguration *getInstance();

    //----parameters
    const static int debounceDelay = 100; //milli-seconds
    const static int holdTime = 1000;     //milli-seconds
    const static int uSwitch_hits_thr = 5;

    //----uSwitches
    const static int open_uSw_pin = 18;
    long open_uSw_last = 0;
    int open_uSw_hits = 0;
    const static int close_uSw_pin = 3;
    long close_uSw_last = 0;
    int close_uSw_hits = 0;

    //----motor
    const static int motorOut1 = 13;
    const static int motorOut2 = 9;
    const static int motorControl = 11;
    const static int motorEncoderPin = 19;
    const static int motorDirectionPin = 12;

    //----pushButtons
    const static int onButton_pin = 2;
    long onButton_last = 0;
    int onButton_hits = 0;

    //----buzzer
    const static int buzzerPin = 5; //PWM

    //----LEDs
    const static int gLED_pin = 7;
    const static int ardLED = 13;

    //----Potentiometer
    const static int Potentiometer_Volume = A8;
    const static int Potentiometer_Cycle = A9;
    const static int Potentiometer_IE = A10;

    void pinConfiguration();
};

#endif
