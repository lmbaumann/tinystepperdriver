/*
* tinystepperdriver.hh - Lightweight library for stepper motor controll on arduino.
* Created by Luca Baumann, 2020.
*/

#ifndef tinystepperdriver_h
#define tinystepperdriver_h

//#include "Arduino.h"
#include <Arduino.h>

class TinyStepperDriver
{
private:
    // Store pins for step and direction outputs
    int pin_step, pin_dir = 0;
    int steps, direction = 0;
    bool active, cancel_current, last_step_pin = false;
    unsigned long last_step_time, duration = 0;

public:
    /*
    * Constructor for TinyStepperDriver
    * pin_step: Pin number top write step operations
    * pin_dir: Direction pin
    */
    TinyStepperDriver(int pin_step, int pin_dir);
    ~TinyStepperDriver();

    /*
    * Initiates a move operation. 
    * steps: Number of steps to be performed by setting the correlating pin to high and low
    * direction: Translates directly to writing to the direction pin
    * duration: Planned duration of the move in milliseconds
    */
    bool move(int steps, int direction, int duration);

    /*
    * Performs the move configured by move(). 
    */
    bool iterate();
    
    /*
    * Stops the current move on the next call of iterate(). 
    */
    void cancel();
};

#ifdef TINYSTEPPERDRIVER_PYTHON_BIND
/*
* Bindings to C for python compatibility
*/
extern "C" {
    TinyStepperDriver* tinystepperdriver_new(int pin_step, int pin_dir){ return new TinyStepperDriver(pin_step, pin_dir); }
    bool tinystepperdriver_move(TinyStepperDriver* drv, int steps, int direction, int duration){ return drv->move(steps, direction, duration); }
    bool tinystepperdriver_iterate(TinyStepperDriver* drv){ return drv->iterate(); }
    void tinystepperdriver_cancel(TinyStepperDriver* drv){ return drv->cancel(); }
}

#endif

#endif