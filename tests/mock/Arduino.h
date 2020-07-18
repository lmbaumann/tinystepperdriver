#ifndef ARDUINO_H
#define ARDUINO_H

#include <iostream>

#define HIGH 1
#define LOW 0
#define OUTPUT 0
#define INPUT 1

#define TINYSTEPPERDRIVER_TIME_MS (unsigned long)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()
#define TINYSTEPPERDRIVER_TIME_US (unsigned long)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()

enum time_modes {normal, iterate};

// reset all variables in this mock implementation
void mock_reset();
void mock_time_mode(time_modes mode);
void mock_time_iteration(int timespan);

void pinMode(int pin, int mode);

void digitalWrite(int pin, int state);

unsigned long micros();

#endif