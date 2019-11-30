#include "main.h"

//GLOBAL INTEGERS TO DEFINE
extern int intakeMotorSpeed;
extern int armMotorSpeed;
extern const double ARMLENGTH;
extern int armAngle;
extern double armHeight;
//HELPER FUNCTIONS

void setArmLift(int power);
/*
Helper Function, simply passes an integer power (-127-127) through to the arm motor.
*/

void setIntake(int power);
/*
Helper Function, simply passes an integer power (-127-127) through to the intake motors.
*/

void setmegaLift(int power);


//DRIVER CODE
void setIntakeMotors();
/*
Ties the lift of the slope to buttons L1 and L2
*/
void setArmMotor();
/*
Ties the lift of the slope to Left and Right buttons.
*/
void setMacroMotors();
//AUTONOMOUS CODE

void intakeIn();

void intakeOut();

void intakeStop();

void armUp();

void armDown();

void armStop();

void armTo(double position, int velocity);
