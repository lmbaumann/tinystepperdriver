#include "Arduino.h"
#include <iostream>
#include <chrono>


unsigned int micros_time = 0;                  // current time in microseconds
time_modes time_mode = time_modes::normal;     // simulated or actual time
int mock_time_iteration_span = 100;            // time span in us to pass per micros call
int digitalWriteHighCounter = 0;               // counter for 


void mock_reset()
{
    time_mode = time_modes::normal;
    micros_time = 0;
    digitalWriteHighCounter = 0;
    mock_time_iteration_span = 100;
}

void mock_time_mode(time_modes mode)
{
    time_mode = mode;
}

void mock_time_iteration(int timespan)
{
    mock_time_iteration_span = timespan;
}

void pinMode(int pin, int mode){}

void digitalWrite(int pin, int state)
{
    if (state == 1) digitalWriteHighCounter += 1;
}

unsigned long micros()
{
    if (time_mode == time_modes::normal) return TINYSTEPPERDRIVER_TIME_US;
    else if (time_mode == time_modes::iterate)
    {
        // each call increase time by 100 us
        micros_time += mock_time_iteration_span;
        return micros_time;
    }
    else return -1;
}