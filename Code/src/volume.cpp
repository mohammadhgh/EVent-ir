#include "volume.h"

volume *volume::INSTANCE = NULL;

volume *volume::getInstance()
{
    if (INSTANCE == NULL)
    {
        INSTANCE = new volume();
    }
    return INSTANCE;
}

int volume::volume_table()
{
    int val = 0;
    val = analogRead(PinConfiguration::volumePin);
    if (val < 150)
    {
        value = 200;
    }
    if (val < 300 && 150 <= val)
    {
        value = 300;
    }
    if (val < 450 && 300 <= val)
    {
        value = 400;
    }
    if (val < 600 && 450 <= val)
    {
        value = 500;
    }
    if (val < 750 && 600 <= val)
    {
        value = 600;
    }
    if (val < 900 && 750 <= val)
    {
        value = 700;
    }
    if (val <= 1023 && 900 <= val)
    {
        value = 800;
    }
    return value;
}