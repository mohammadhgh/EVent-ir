#include "alarm.h"

ALARM::ALARM()
{

    // this->buzz = new Buzzer(PinConfiguration::buzzerPin);
    this->led = new LED(PinConfiguration::ardLED);
}
void ALARM::alarm(int level)
{
    tone(pin, sound_freq, on_delay);
    digitalWrite(8, 1);
    delay(on_delay);
    noTone(pin);
    digitalWrite(8, 0);
    delay(on_delay);
}