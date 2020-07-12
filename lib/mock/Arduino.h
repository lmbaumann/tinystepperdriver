/*
* Arduino.h - Mock for Arduino.h from the arduino standard library.
* Creates logging functions for the python bindings.
* Created by Luca Baumann, 2020.
*/
#ifndef ARDUINO_H
#define ARDUINO_H

#include <iostream>
#include <fstream>
#include <string> 
#include <chrono>

//using namespace std;

#define HIGH 1
#define LOW 0
#define OUTPUT 0
#define INPUT 1

#define TINYSTEPPERDRIVER_TIME_MS (unsigned long)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()
#define TINYSTEPPERDRIVER_TIME_US (unsigned long)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()


bool first_file_access_digitalWrite = true;
bool first_file_access_general = true;

void pinMode(int pin, int mode){}

void digitalWrite(int pin, int state)
{
    // Write log to file in CSV style
    std::ofstream logfile;

    if (first_file_access_digitalWrite)
    {
        first_file_access_digitalWrite = false;
        logfile.open("log_digitalWrite.txt", std::ios::trunc);
        logfile << "time,pin,state\n";
    } 
    else
    {
        logfile.open("log_digitalWrite.txt", std::ios::app);
    }
    logfile << TINYSTEPPERDRIVER_TIME_MS << "," << pin << "," << state << "\n";
    logfile.close();
}

void general_log(std::string text)
{
    std::ofstream logfile;

    if (first_file_access_general)
    {
        first_file_access_general = false;
        logfile.open("log_general.txt", std::ios::trunc);
    } 
    else
    {
        logfile.open("log_general.txt", std::ios::app);
    }
    logfile << TINYSTEPPERDRIVER_TIME_MS << "," << text << "\n";
    logfile.close();
}

unsigned long millis()
{
    return TINYSTEPPERDRIVER_TIME_MS;
}

unsigned long micros()
{
    return TINYSTEPPERDRIVER_TIME_US;
}

#endif