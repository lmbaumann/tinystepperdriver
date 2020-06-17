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

#ifdef C_LIB
/*
* Bindings to C for python compatibility
*/
extern "C" {
    tinystepperdriver* tinystepperdriver_new(int pin_step, int pin_dir){ return new tinystepperdriver(pin_step, pin_dir); }
    bool tinystepperdriver_move(tinystepperdriver* drv, int steps, int direction, int duration){ return drv->move(steps, direction, duration); }
    bool tinystepperdriver_iterate(tinystepperdriver* drv){ return drv->iterate(); }
    void tinystepperdriver_cancel(tinystepperdriver* drv){ return drv->cancel(); }
}

#endif

#endif