#ifndef LCD_h
#define LCD_h

#include <Arduino.h>
#include <avr/wdt.h>
#include <openGLCD.h>
#include <sysconfig.h>
#include <configuration.h>
#include <PressureSensor.h>
//#include <gText.h>
#include <animation.h>
#define LogoDelay 200 / 3

class LCD
{
private:
    static LCD *INSTANCE;
    SysConfig *local_sysconfig;
    PressureSensor *pr;
    String lastRate = "0";
    String lastVol = "0";
    String lastIE = "0";
    String lastPR = "0";

    int x = 0; //x graph coordinate
    int y = 0; //y graph coordinate
    int q = 0; //old x graph coordinate
    int w = 0; //old y graph coordinate

    int printVarCounter = 0;
    bool wipeVar[4] = {true, true, true, true};
public:
    LCD();
    static LCD *getInstance();
    void update_sysconfig(SysConfig *newconfig);
    void LCD_Menu(int tidalVolume, int respRate, int IEratio, float PR);
    void LCD_Clear();
    void LCD_Logo();
    void LCD_Cover();
    void LCD_graph();
    void wipeVariable(int hpos, int vpos, int spaceQuantity);
    String printVariable(int hpos, int ypos, bool *wipeWar, String toPrint, String *lastToPrint);
    
};

#endif