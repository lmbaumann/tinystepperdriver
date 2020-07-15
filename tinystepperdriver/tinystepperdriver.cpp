/*
* tinystepperdriver.cpp - Lightweight library for stepper motor controll on arduino.
* Created by Luca Baumann, 2020.
*/

//#define TINYSTEPPERDRIVER_DEBUG
#include "tinystepperdriver.hpp"

#ifdef TINYSTEPPERDRIVER_PYTHON_BIND
using  namespace std;
#else
#ifdef TINYSTEPPERDRIVER_DEBUG
String to_string(int val)
{
  return String(val);
}
String to_string(unsigned long val)
{
  return String(val);
}

void general_log(String text)
{
  char buf[100];
  text.toCharArray(buf, 100);
  Serial.println(buf);
}
#endif
#endif

TinyStepperDriver::TinyStepperDriver(unsigned int pin_step, unsigned int pin_dir)
{
    if (pin_step == pin_dir) TinyStepperDriver::initialized = false;
    else
    {
        TinyStepperDriver::pin_step = pin_step;
        TinyStepperDriver::pin_dir = pin_dir;

        // Set pin modes
        pinMode(pin_step, OUTPUT);
        pinMode(pin_dir, OUTPUT);

        TinyStepperDriver::initialized = true;
    }
}

TinyStepperDriver::~TinyStepperDriver()
{
}

bool TinyStepperDriver::is_initialized()
{
    return initialized;
}

bool TinyStepperDriver::move(unsigned int n_steps, unsigned int dir, unsigned long duration_ms)
{
    if (!initialized || active)
    {
        // If there is a move currently running, refuse new configuration since no pipeline is defined
        return false;
    }
    else
    {
        // Sanity checks
        if (n_steps > duration_ms) return false; // Assuming maximum speed of 1 step/millisecond based on tests of A4988

        // Initialize executing move
        TinyStepperDriver::active = true;
        TinyStepperDriver::steps = n_steps * 2; // steps is used to enable and disable step output pin, so double count is needed
        TinyStepperDriver::direction = dir;
        TinyStepperDriver::duration = duration_ms * 1000; // convert to microseconds
        TinyStepperDriver::last_step_time = micros();
        TinyStepperDriver::last_step_pin = false;

        // Set direction
        digitalWrite(pin_dir, direction);
    }
    
#ifdef TINYSTEPPERDRIVER_DEBUG
    general_log("move," + to_string(TinyStepperDriver::steps) + "," + to_string(TinyStepperDriver::direction) + "," + to_string(TinyStepperDriver::duration) + ",,");
#endif
    
    return true;
}

bool TinyStepperDriver::move(int n_steps, unsigned long duration_ms)
{
    return TinyStepperDriver::move(abs(n_steps), n_steps > 0, duration_ms);
}

bool TinyStepperDriver::iterate()
{
    if (initialized && active)
    {
        // test for end condition
        if (cancel_current || (steps <= 0 && duration <= 0))
        {
            cancel_current = false;

            // reset pins to low
            digitalWrite(pin_step, LOW);
            digitalWrite(pin_dir, LOW);

            // disable execution
            active = false;
            return false;
        }

        // check if the timing condition for a step is met
        unsigned long time_since_step = micros() - last_step_time;
        unsigned long wanted_duration = duration;
        if (steps > 0)
        {
            wanted_duration = duration / (unsigned long)steps;
        }
        

        if (time_since_step >= wanted_duration)
        {

            // do step if steps to do
            if (steps > 0)
            {
                last_step_pin = !last_step_pin;
                digitalWrite(pin_step, last_step_pin);
            }

            // update variables
            steps--;
            last_step_time = micros();
            if (duration < time_since_step) duration = 0;
            else duration -= time_since_step;

#ifdef TINYSTEPPERDRIVER_DEBUG
            general_log("iterate," + to_string(TinyStepperDriver::steps) + "," + to_string(TinyStepperDriver::duration) + "," + to_string(TinyStepperDriver::last_step_time) + "," + to_string(time_since_step) + "," + to_string(wanted_duration));
#endif
        }
        return true;
    }
    else return false;
}

void TinyStepperDriver::cancel()
{
    if (TinyStepperDriver::active)
    {
        TinyStepperDriver::cancel_current = true;
    }
}
