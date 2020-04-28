#include "main.h"
extern int armPower;

void setMegaLift(int power);

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
