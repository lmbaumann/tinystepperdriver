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
    TinyStepperDriver drv = TinyStepperDriver(1, 2);  // should just work normally
    errors += !drv.is_initialized();

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
    TinyStepperDriver drv = TinyStepperDriver(1, 1);  // should not work
    errors += drv.is_initialized();

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
    errors += drv.is_initialized() != true;
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
    errors += drv.is_initialized() != true;
    errors += drv.move(10, 20) != true;   // first request should work
    errors += drv.move(10, 20) != false;  // second request should fail, since first is not done yet

    // cleanup
    mock_reset();
    print_test_errors("test_tinystepperdriver_move_initialize_double", errors);
    
    return errors;
}

int test_tinystepperdriver_iterate()
{
    // prerequisits
    mock_reset();
    mock_time_mode(time_modes::iterate);
    mock_time_iteration(1000);
    TinyStepperDriver drv = TinyStepperDriver(1, 2);
    int errors = 0;

    // test
    errors += drv.is_initialized() != true;
    errors += drv.move(1, 2) != true;
    errors += drv.iterate() != true;
    errors += drv.iterate() != true;
    errors += drv.iterate() == true;

    // cleanup
    mock_reset();
    print_test_errors("test_tinystepperdriver_iterate", errors);
    
    return errors;
}

int test_tinystepperdriver_cancel()
{
    // prerequisits
    mock_reset();
    TinyStepperDriver drv = TinyStepperDriver(1, 2);
    int errors = 0;

    // test
    errors += drv.move(10, 20) != true;   // first request should work
    drv.cancel();
    errors += drv.iterate() == true;
    errors += drv.move(10, 20) != true;   // third request should work again

    // cleanup
    mock_reset();
    print_test_errors("test_tinystepperdriver_cancel", errors);
    
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
    res += test_tinystepperdriver_iterate();
    res += test_tinystepperdriver_cancel();

    std::cout << res << " errors occured." << std::endl;
    std::cout << "*** Tests done ***" << std::endl;
	return res;
}

#endif