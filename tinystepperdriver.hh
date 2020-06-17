/*
* tinystepperdriver.h - Lightweight library for stepper motor controll on arduino
* Created by Luca Baumann.
*/

#ifndef tinystepperdriver_h
#define tinystepperdriver_h

#include "Arduino.h"

class tinystepperdriver
{
private:
    int pin_step, pin_dir = 0;
    int steps, direction, duration = 0;
    bool active, cancel_current, last_step_pin = false;
    unsigned long last_step_time = 0;
public:
    tinystepperdriver(int, int);
    ~tinystepperdriver();

    /*
    * Initiates a move operation. 
    */
    bool move(int, int, int);
    bool iterate();
    void cancel();
};

#endif