#ifndef LCD_h
#define LCD_h
#include <Arduino.h>
#include <avr/wdt.h>
#include <openGLCD.h>
#include <sysconfig.h>
#include <configuration.h>

class LCD
{
private:
    static LCD *INSTANCE;
    SysConfig local_sysconfig;

public:
    static LCD *getInstance();
    void update_sysconfig(SysConfig *newconfig);
    void LCD_Menu();
    void LCD_Clear();
    void LCD_Cover();
};

#endif