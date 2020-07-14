#include <LCD.h>

LCD *LCD::INSTANCE = NULL;

LCD::LCD()
{
    this->local_sysconfig = new SysConfig(0, 0, 0);
    this->lastRate = 0;
    this->lastVol = 0;
}
LCD *LCD::getInstance()
{
    if (INSTANCE == NULL)
    {
        INSTANCE = new LCD();
    }
    return INSTANCE;
}

void LCD::update_sysconfig(SysConfig *newconfig)
{
    this->local_sysconfig->update(newconfig);
}

void LCD::LCD_Cover()
{
    GLCD.Init();
    GLCD.DrawRoundRect(0, 0, GLCD.Width, GLCD.Height, 4);
    GLCD.SelectFont(cp437font8x8);
    GLCD.DrawString(F("Save Breathe"), gTextfmt_center, 25);
    GLCD.DrawString(F("Save Life"), gTextfmt_center, 35);
    
}
void LCD::LCD_Clear()
{
    GLCD.ClearScreen();
}

void LCD::LCD_Menu(int tidalVolume, int respRate)
{
    //int tidalVolume = this->local_sysconfig->get_Tidal_Volume();
    //int respRate = this->local_sysconfig->get_Resp_Rate();

    int *tidal_Vol = &(this->lastVol);
    int *resp_Rate = &(this->lastRate);

    GLCD.DrawRoundRect(0, 0, GLCD.Width, GLCD.Height, 2);
    GLCD.SelectFont(Iain5x7);

    for (size_t i = 0; i < 64; i += 16)
    {
        GLCD.DrawLine(0, 16 + i, GLCD.Width, 16 + i);
        GLCD.DrawLine(0, 17 + i, GLCD.Width, 17 + i);
    }

    GLCD.DrawString(F("Tidal Volume : "), 3, 3);
    GLCD.CursorTo((int8_t)16);
    GLCD.print(screenWiper((int8_t)16, tidalVolume, tidal_Vol));

    GLCD.DrawString(F("Resp Rate : "), 3, 19);
    GLCD.CursorTo((int8_t)16);
    GLCD.print(screenWiper((int8_t)16, respRate, resp_Rate));

    GLCD.DrawString(F("In/Ex Ratio: "), 3, 36);
    GLCD.CursorTo(16);
    GLCD.print(1);

    GLCD.DrawString(F("Pressure Sen : "), 3, 53);
    GLCD.CursorTo(16);
    GLCD.print(1);
}

int LCD::screenWiper(int8_t columnNumber, int toPrint, int *lastToPrint)
{
    if (toPrint != *lastToPrint)
    {
        GLCD.print("          ");
        GLCD.CursorTo(columnNumber);
        *lastToPrint = toPrint;
    }
    return toPrint;
}
