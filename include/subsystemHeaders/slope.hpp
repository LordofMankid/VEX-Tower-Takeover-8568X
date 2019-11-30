#include "main.h"

//GLOBAL INTEGERS TO DEFINE
#define SLOPE_GEAR_RATIO 21.0
extern double slopeMaxAngle;
extern double slopeAngle;
extern const double slopeThreshold;

//HELPER FUNCTIONS
void setSlopeLift(int power);
/*
Helper Function, simply passes an integer power (-127-127) through to the slope motor.
*/
//DRIVER CODE
void setSlopeMotors();
/*
Ties the lift of the slope to buttons R1(in) and L1(out)
*/

//AUTONOMOUS CODE
void slopeUp(int targetAngle, int maxSpeed);

void slopeDown(int targetAngle);
