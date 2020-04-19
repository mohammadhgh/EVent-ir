#ifndef LCD_h
#define LCD_h
#include <Arduino.h>
#include <avr/wdt.h>
#include <openGLCD.h>
#include <sysconfig.h>
#include <configuration.h>
#include <gText.h>

class LCD
{
private:
    static LCD *INSTANCE;
    SysConfig *local_sysconfig;
    int wipeCounter = 0;
    int lastRate = 0;
    int lastVol = 0;
    // int lastIX = 0;

public:
    LCD();
    static LCD *getInstance();
    void update_sysconfig(SysConfig *newconfig);
    void LCD_Menu(int tidalVolume, int respRate);
    void LCD_Clear();
    void LCD_Cover();
    int screenWiper(int8_t columnNumber, int toPrint, int *lastToPrint);
};

#endif