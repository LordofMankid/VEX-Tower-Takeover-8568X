#include "main.h"
#include "driveAuton.hpp"
#include "intakeArmAuton.hpp"
#include "slopeAuton.hpp"
//VARIABLES
extern bool autonRunning;
extern int delayTick;
extern int delayStep;
void setAutonButton();

/////////////////
//AUTON TESTS
/////////////////

//HELPER

void autonUpdate();

void coolDelay(int time, int targDriveStep);

void adjustkPID(kPID kPID, double kP, double kI, double kD, int driveStep);

void delay(int time, int targDriveStep);

//TESTS
void armTest();

void driveTest();
void autonDriveTest();

void autonTest();

void slopeTest();
void protectedBlue();
void protectedRed();
void autonCorrect();

void intakeTest();

void multipleSubsystemTest();

void redStackFive();

void blueFiveStack();

void redFiveStack();

void scoreTurnLeft();

void autonSkills();

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
