#ifndef LCD_h
#define LCD_h

#include <Arduino.h>
#include <avr/wdt.h>
#include <openGLCD.h>
#include <sysconfig.h>
#include <configuration.h>
#include <PressureSensor.h>
#include <animation.h>
#include <HX711.h>

#define LogoDelay 200 / 3

class LCD
{
private:
    static LCD *INSTANCE;
    SysConfig *local_sysconfig;
    PressureSensor *pr;
    int lastRate = 0;
    int lastVol = 0;
    int lastIE = 0;
    int lastPR = 0;
    int x = 0;
    int y = 0;
    int q = 0;
    int w = 0;
    int count = 0;

public:
    LCD();
    static LCD *getInstance();
    void update_sysconfig(SysConfig *newconfig);
    void LCD_Menu(int tidalVolume, int respRate, int IEratio, float PR);
    void LCD_Clear();
    void LCD_Logo();
    void LCD_Cover();
    void LCD_graph();
    int screenWiper(int columnnumber, int toPrint, int *lastToPrint);
};

#endif