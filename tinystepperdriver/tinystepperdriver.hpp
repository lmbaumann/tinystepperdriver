/*
* tinystepperdriver.hpp - Lightweight library for stepper motor controll on arduino.
* Created by Luca Baumann, 2020.
*/

#ifndef TINYSTEPPERDRIVER_H
#define TINYSTEPPERDRIVER_H

#include <Arduino.h>

class TinyStepperDriver
{
private:
    // Store pins for step and direction outputs
    int pin_step = 0, pin_dir = 0;
    int steps = 0, direction = 0;
    bool active = false, cancel_current = false, last_step_pin = false, initialized = false;
    unsigned long last_step_time = 0, duration = 0;

public:
    /*
    * Constructor for TinyStepperDriver
    * pin_step: Pin number top write step operations
    * pin_dir: Direction pin
    */
    TinyStepperDriver(unsigned int pin_step, unsigned int pin_dir);
    ~TinyStepperDriver();

    /*
    * Returns true if driver is ready for use.
    */
    bool is_initialized();

    /*
    * Initiates a move operation. 
    * steps: Number of steps to be performed by setting the correlating pin to high and low
    * direction: Translates directly to writing to the direction pin
    * duration: Planned duration of the move in milliseconds
    */
    bool move(unsigned int n_steps, unsigned int dir, unsigned long duration_ms);
    bool move(int n_steps, unsigned long duration_ms);

    /*
    * Performs the move configured by move(). 
    * Returns true while executing a move.
    */
    bool iterate();
    
    /*
    * Stops the current move on the next call of iterate(). 
    */
    void cancel();
};


// Use definition to configure build for pyhton binding
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