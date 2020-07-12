#include <tinystepperdriver.hpp>

#include <iostream>

#ifndef _MAIN_
#define _MAIN_

int test_tinystepperdriver_move()
{
    TinyStepperDriver drv = TinyStepperDriver(1, 2);
    return 0;
}

int main(int argc, char* argv[]) {
    std::cout << "*** Running tests ***" << std::endl;

    int res = 0;
    res += test_tinystepperdriver_move();

    std::cout << res << " errors occured." << std::endl;
    std::cout << "*** Tests done ***" << std::endl;
	return res;
}

#endif