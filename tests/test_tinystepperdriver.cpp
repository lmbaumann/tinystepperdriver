#include <tinystepperdriver.hpp>
#include <Arduino.h>

#include <iostream>
#include <string>

#ifndef _MAIN_
#define _MAIN_

using namespace std;

/*
* General purpose functions. More are defined in Arduino.h
*/
void print_test_errors(string name, int errors)
{
    cout << "Test " << name << " returned " << errors << " errors." << endl;
}

/*
* Test functions
*/
int test_tinystepperdriver_constructor()
{
    // prerequisits
    mock_reset();
    int errors = 0;

    // test
    try
    {
        TinyStepperDriver drv = TinyStepperDriver(1, 2);  // should just work normally
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        errors = 1;
    }

    // cleanup
    mock_reset();
    print_test_errors("test_tinystepperdriver_constructor", errors);
    
    return errors;
}

int test_tinystepperdriver_constructor_double_pin()
{
    // prerequisits
    mock_reset();
    int errors = 0;

    // test
    try
    {
        TinyStepperDriver drv = TinyStepperDriver(1, 1);  // should not work
        errors = 1;
    }
    catch(const exception& e)
    {
        // this is fine
    }

    // cleanup
    mock_reset();
    print_test_errors("test_tinystepperdriver_constructor_double_pin", errors);
    
    return errors;
}

int test_tinystepperdriver_move_initialize()
{
    // prerequisits
    mock_reset();
    TinyStepperDriver drv = TinyStepperDriver(1, 2);
    int errors = 0;

    // test
    errors += drv.move(10, 21) != true;

    // cleanup
    mock_reset();
    print_test_errors("test_tinystepperdriver_move_initialize", errors);
    
    return errors;
}

int test_tinystepperdriver_move_initialize_double()
{
    // prerequisits
    mock_reset();
    TinyStepperDriver drv = TinyStepperDriver(1, 2);
    int errors = 0;

    // test
    errors += drv.move(10, 20) != true;   // first request should work
    errors += drv.move(10, 20) != false;  // second request should fail, since first is not done yet

    // cleanup
    mock_reset();
    print_test_errors("test_tinystepperdriver_move_initialize_double", errors);
    
    return errors;
}

/*
* Main to execute all test functions
*/
int main(int argc, char* argv[]) {
    std::cout << "*** Running tests ***" << std::endl;

    int res = 0;
    res += test_tinystepperdriver_constructor();
    res += test_tinystepperdriver_constructor_double_pin();
    res += test_tinystepperdriver_move_initialize();
    res += test_tinystepperdriver_move_initialize_double();

    std::cout << res << " errors occured." << std::endl;
    std::cout << "*** Tests done ***" << std::endl;
	return res;
}

#endif