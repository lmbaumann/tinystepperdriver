/*
* Arduino.h - Mock for the Arduino.h from the arduino standard library.
* Created by Luca Baumann
*/
#ifndef arduino_h
#define arduino_h

#include <ctime>
#include <iostream>

//using namespace std;

#define HIGH 1
#define LOW 0

void digitalWrite(int pin, int state)
{
    std::cout << "Writing pin " << pin << " state " << state << std::endl;
}

unsigned long millis()
{
    return (unsigned long) (time(0)*1000);
}

#endif