#include <LCD.h>

LCD *LCD::INSTANCE = NULL;

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
    GLCD.DrawRoundRect(0, 0, 128, 64, 4);
    Serial.println("Setup");
    GLCD.SelectFont(cp437font8x8);
    GLCD.DrawString(F("Save Breathe"), gTextfmt_center, 25);
    GLCD.DrawString(F("Save Life"), gTextfmt_center, 35);
    
}
void LCD::LCD_Clear()
{
    GLCD.ClearScreen();
}

void LCD::LCD_Menu()
{
    int tidalVolume = this->local_sysconfig->get_Tidal_Volume();
    int respRate = this->local_sysconfig->get_Resp_Rate();
    int IEratio = this->local_sysconfig->get_IE_Ratio();

    GLCD.DrawRoundRect(0, 0, GLCD.Width, GLCD.Height, 2);
    GLCD.SelectFont(Iain5x7);

    for (size_t i = 0; i < 64; i += 16)
    {
        GLCD.DrawLine(0, 16 + i, GLCD.Width, 16 + i);
        GLCD.DrawLine(0, 17 + i, GLCD.Width, 17 + i);
    }

    GLCD.DrawString(F("Tidal Volume : "), 3, 3);
    GLCD.CursorTo(16);
    GLCD.print(tidalVolume);

    GLCD.DrawString(F("Resp Rate : "), 3, 19);
    GLCD.CursorTo(16);
    GLCD.print(respRate);

    GLCD.DrawString(F("In/Ex Ratio: "), 3, 36);
    GLCD.CursorTo(16);
    GLCD.print(IEratio);

    GLCD.DrawString(F("Pressure Sen : "), 3, 53);
    GLCD.CursorTo(16);
    GLCD.print(1);
}
