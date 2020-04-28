#include "main.h"

//GLOBAL INTEGERS TO DEFINE
extern int intakeMotorSpeed;
extern int armMotorSpeed;
extern const double ARMLENGTH;
extern int armAngle;
extern double armHeight;
extern bool intakeOn;
extern kPID armPID;
extern bool armOn;
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
void armMove(int targetAngle, int maxSpeed, int driveStepNumber, int armStepNumber);

void startIntake(int targetTime, int speed, int driveStepNumber, int timeReachedNumber);

void intakeMove(int targetTime, int speed, int driveStepNumber, int timeReachedNumber);

void intakeTime(int targetTime, int speed);

void intakeIn();

void intakeOut();

void intakeStop();

void armUp();

void armDown();

void armStop();

void armTo(double position, int velocity);
