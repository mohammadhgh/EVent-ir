#ifndef volume_h
#define volume_h

#include <Arduino.h>
#include <avr/wdt.h>

class volume
{
private:
    static volume *INSTANCE;
    int value = 0;

public:
    static volume *getInstance();
    int volume_table();
};

#endif