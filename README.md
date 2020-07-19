# Tinystepperdriver

This is a small project for me to learn how to drive a stepper motor with default step and direction interface on arduino.
It is aimed at controlling a stepper motor driver by staging moves consisting of number of steps, direction and duration.

Constraints:
- Only one move can be staged at a time (no pipeline implemented)
- Only linear step interpolation over time

## Contents

### Stepper motor driver

The steper driver consists of a single class that does step generation and I/O handling.

### Arduino example

tinystepperdriver/tinystepperdriver.ino contains a minimal working example on how to use the driver.

### Python binding

lib contains all files necessary to build and use this library in python.

lib/test_py_wrapper.ipynb contains a working example on how to use the python library from lib/tinystepperdriver.py.

## Compiling

Running 'make' in the base repository builds the tests in the /tests folder and executes them. If they succeed, the driver is build as dynamic link library in the /lib folder.