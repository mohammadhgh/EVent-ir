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
    const static int debounceDelay = 10; //milli-seconds
    const static int holdTime = 1000;     //milli-seconds
    const static int uSwitch_hits_thr = 5;

    //----uSwitches
    const static int open_uSw_pin = 3;
    long open_uSw_last = 0;
    int open_uSw_hits = 0;
    const static int close_uSw_pin = 5;
    long close_uSw_last = 0;
    int close_uSw_hits = 0;

    //----motor
    const static int motorOut1         = 18;
    const static int motorOut2         = 17;
    const static int motorControl      = 7;
    const static int motorEncoderPin   = 21;
    const static int motorDirectionPin = 20;
    const static int motorDriverOnOff  = 16;

    //----pushButtons
    const static int onButton_pin = 2;

    //----buzzer
    const static int buzzerPin = 48; //PWM

    //----LEDs
    const static int bLED_pin = 43;
    const static int wLED_pin = 47;
    const static int ardLED = 13;

    //----Potentiometer
    const static int Potentiometer_Volume = A8;
    const static int Potentiometer_Cycle = A10;
    const static int Potentiometer_IE = A12;

    //Dummy Input Pin
    const static int dummyInput = 15;

    void pinConfiguration();
};

#endif
