# Tinystepperdriver

This is a small project for me to learn how to drive a stepper motor with default step and direction interface on arduino.
It is aimed at controlling a stepper motor driver  by staging moves consisting of number of steps, direction and duration.

Constraints:
- Only one move can be staged at a time (no pipeline implemented)
- Only linear interpolation

## Arduino example

tinystepperdriver.ino contains a minimal working example on how to use the driver.

## Python binding

lib contains all files necessary to build and use this library in python.

To build the library, run "make" in the lib directory.

lib/test_py_wrapper.ipynb contains a working example on how to use the python library from lib/tinystepperdriver.py.

## Todo

- Write tests in C++, python interface is insufficient