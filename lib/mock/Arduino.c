#include "Arduino.h"


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