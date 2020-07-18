/*
* tinystepperdriver.ino - Example use of tinystepperdriver library on arduino with RAMPS 1.4 extension board and stepper driver on E0
* Created by Luca Baumann, 2020.
*/
#define TINYSTEPPERDRIVER_DEBUG

#include "tinystepperdriver.hpp"


#define PIN_STEP 26
#define PIN_DIR 28
#define PIN_EN 24
#define PIN_LED 13

// Create class instance with correct pin mappings
TinyStepperDriver driver(PIN_STEP, PIN_DIR);

void setup() {
#ifdef TINYSTEPPERDRIVER_DEBUG
  Serial.begin(9600);
#endif
  // Initiate a move with 200 steps, direction 1 in 1 second (1000 ms)
  driver.move(-200, 200);
  pinMode(PIN_EN, OUTPUT);
  digitalWrite(PIN_EN, LOW);
}

void loop() {
  // execute staged move
  driver.iterate();
}
