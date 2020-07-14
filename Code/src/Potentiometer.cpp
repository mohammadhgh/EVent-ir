#include "Potentiometer.h"

Potentiometer::Potentiometer(int pin, int subMultiple)
{

    this->pin = pin;
    this->subMultiple = subMultiple;
}

void Potentiometer::set_Range(int *table, uint8_t size)
{
    this->table = new int[size];
    memcpy(this->table, table, size);
    this->size = size;
}

int Potentiometer::Potentiometer_Read()
{
    int volumeValue = analogRead(this->pin);

    int volumeDisplay;
    int Range_Value[this->subMultiple] = {};
    this->subValue = 1023 / this->subMultiple;

    for (int i = 1; i <= this->subMultiple; i++)
    {
        Range_Value[i - 1] = i * (this->subValue);
    }

    if (volumeValue <= Range_Value[0])
    {

        volumeDisplay = this->table[0];
    }

    if (volumeValue > Range_Value[this->subMultiple - 1])
    {
        volumeDisplay = this->table[this->subMultiple - 1];
    }

    for (int i = 0; i < (this->subMultiple - 1); i++)
    {
        if (volumeValue > Range_Value[i] && volumeValue < Range_Value[i + 1])
        {
            volumeDisplay = this->table[i + 1];
        }
    }

    return volumeDisplay;
}
