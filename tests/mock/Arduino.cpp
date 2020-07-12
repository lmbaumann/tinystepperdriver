#include "Arduino.h"
#include <iostream>
#include <chrono>

void pinMode(int pin, int mode){}

void digitalWrite(int pin, int state)
{
    std::cout << TINYSTEPPERDRIVER_TIME_MS << "," << pin << "," << state << "\n";
}

unsigned long millis()
{
    return TINYSTEPPERDRIVER_TIME_MS;
}

unsigned long micros()
{
    return TINYSTEPPERDRIVER_TIME_US;
}