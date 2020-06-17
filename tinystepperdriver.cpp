#include "tinystepperdriver.h"

tinystepperdriver::tinystepperdriver(int pin_step, int pin_dir)
{
    tinystepperdriver::pin_step = pin_step;
    tinystepperdriver::pin_dir = pin_dir;
}

tinystepperdriver::~tinystepperdriver()
{
}

bool tinystepperdriver::move(int steps, int direction, int duration)
{
    if (active)
    {
        return false;
    }
    else
    {
        // Sanity checks
        if (steps > duration) return false; // Assuming maximum speed of 1 step/millisecond

        // Initialize executing move
        tinystepperdriver::active = true;
        tinystepperdriver::steps = steps * 2; // steps is used to enable and disable step output pin
        tinystepperdriver::direction = direction;
        tinystepperdriver::duration = duration;
        tinystepperdriver::last_step_time = millis();
        tinystepperdriver::last_step_pin = false;

        // write direction
        digitalWrite(pin_dir, direction);

        return true;
    }
    
}

bool tinystepperdriver::iterate()
{
    if (active)
    {
        // test for end condition
        if (cancel_current || duration <= 0)
        {
            cancel_current = false;

            // reset pins to low
            digitalWrite(pin_step, LOW);
            digitalWrite(pin_dir, LOW);

            // disable execution
            active = false;
        }

        // check if the timing condition for a step is met
        unsigned long time_since_step = millis() - last_step_time;

        if (time_since_step > duration / steps)
        {
            // do step if steps to do
            if (steps > 0)
            {
                last_step_pin = !last_step_pin;
                digitalWrite(pin_step, last_step_pin);
            }

            // update variables
            steps--;
            duration -= time_since_step;
            last_step_time = millis();
        }
        return true;
    }
    else return false;
}

void tinystepperdriver::cancel()
{
    if (active)
    {
        cancel_current = true;
    }
}

/*
* Bindings to C for python compatibility
*/
extern "C" {
    tinystepperdriver* tinystepperdriver_new(){ return new tinystepperdriver(); }
    bool tinystepperdriver_move(tinystepperdriver* drv, int steps, int direction, int duration){ return drv->move(steps, direction, duration); }
    bool tinystepperdriver_iterate(tinystepperdriver* drv){ return drv->iterate(); }
    void tinystepperdriver_cancel(tinystepperdriver* drv){ return drv->cancel(); }
}