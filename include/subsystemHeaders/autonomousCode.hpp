#include "main.h"

//VARIABLES
extern bool autonRunning;


void setAutonButton();

/////////////////
//AUTON TESTS
/////////////////

//HELPER
void autonUpdate();


void adjustkPID(kPID kPID, double kP, double kI, double kD, int driveStep);

void delay(int time, int targDriveStep);

//TESTS

void autonDriveTest();

void autonTest();

void slopeTest();

void autonCorrect();

void intakeTest();

void multipleSubsystemTest();

void redStackFive();

void blueStackFive();

void scoreTurnLeft();

void scoreTurnRight();
/*void autonTurn();

void autonOne();

void autonTwo();

void autonCorrect();

void autonStackFiveRed();

void autonStackFiveBlue();

void autonStackNine();

void scoreOneLeft();

void scoreOneRight();*/

void autonSkills();
