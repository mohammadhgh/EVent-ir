#ifndef LCD_h
#define LCD_h
#include <Arduino.h>
#include <avr/wdt.h>
#include <openGLCD.h>
#include <sysconfig.h>
#include <configuration.h>
#include <../lib/openGLCD/include/gText.h>


class LCD
{
private:
    static LCD *INSTANCE;
    SysConfig *local_sysconfig;

    String lastRate = "0";
    String lastVol = "0";
    String lastIE = "0";
    // int lastIX = 0;

public:
    LCD();
    static LCD *getInstance();
    void update_sysconfig(SysConfig *newconfig);
    void LCD_Menu(int tidalVolume, int respRate, int IEratio);
    void LCD_Clear();
    void LCD_Cover();
    String screenWiper(int columnnumber, String toPrint, String *lastToPrint);
};

#endif