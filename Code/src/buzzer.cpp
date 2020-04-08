#include <buzzer.h>

Buzzer *Buzzer::INSTANCE = NULL;

Buzzer *Buzzer::getInstance()
{
    if (INSTANCE == NULL)
    {
        INSTANCE = new Buzzer();
    }
    return INSTANCE;
}

void Buzzer::beep(int beeps_count)
{
    for(int i=0; i<beeps_count; i++)
    {
        analogWrite(PinConfiguration::buzzerPin, sound_freq);
        delay(on_delay);
        analogWrite(PinConfiguration::buzzerPin, 0);
        delay(on_delay);
        analogWrite(PinConfiguration::buzzerPin, sound_freq);
        delay(on_delay);
        analogWrite(PinConfiguration::buzzerPin, 0);
        delay(on_delay);
        analogWrite(PinConfiguration::buzzerPin, sound_freq);
        delay(on_delay);
        analogWrite(PinConfiguration::buzzerPin, 0);
        delay(on_delay);
        analogWrite(PinConfiguration::buzzerPin, 0);
        delay(off_delay);
    }
}