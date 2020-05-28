#include "Potentiometer.h"

Potentiometer::Potentiometer(int pin, int subMultiple)
{

    this->pin = pin;
    this->subMultiple = subMultiple;
    this->volumeDisplay = 0;
    this->lastVolumeValue = 0;
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

    int Range_Value[this->subMultiple] = {};
    this->subValue = 1023 / this->subMultiple;
    if (volumeValue != this->lastVolumeValue)
    {

        for (int i = 1; i <= this->subMultiple; i++)
        {
            Range_Value[i - 1] = i * (this->subValue);
        }
        int margin = Range_Value[0] / 2;

        if (volumeValue <= Range_Value[0] - margin || volumeValue <= Range_Value[0] + margin)
        {

            this->volumeDisplay = this->table[0];
        }

        if (volumeValue > Range_Value[this->subMultiple - 1] + margin || volumeValue > Range_Value[this->subMultiple - 1] - margin)
        {
            this->volumeDisplay = this->table[this->subMultiple - 1];
        }

        for (int i = 0; i < (this->subMultiple - 1); i++)
        {
            if ((volumeValue > Range_Value[i] + margin || volumeValue > Range_Value[i] - margin) && (volumeValue < Range_Value[i + 1] + margin || volumeValue < Range_Value[i + 1] - margin))
            {
                this->volumeDisplay = this->table[i + 1];

                break;
            }
        }
        this->lastVolumeValue = volumeValue;
    }
    return this->volumeDisplay;
}