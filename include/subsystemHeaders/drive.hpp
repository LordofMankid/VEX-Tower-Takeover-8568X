#include "main.h"

extern int drive_yPower;
extern int drive_xPower;
extern int drive_rPower;

extern int driveFactor;
extern double KpDrive;
extern double KdDrive;
extern double KiDrive;

//auton variables

extern bool firstCycle;
extern int driveStep;
extern double distanceFromInitial;
extern double initTargetDistance;

void translateY(double unitsY, double maxSpeed);
//helper functions

/*
setDrive takes three integer parameters, effective from -127 - 127)
1. Power for movement along the Y-axis
2. Power for movement along the X-axis
3. Power for rotation(positive being clockwise)\
Yes, they can be combined. No worries about them having to add up to 127
*/
void setDrive(int yPower, int rPower);

void setDriveAuton(double yDistance, double xDistance, double rDistance, int power);

/*
Resets the position of the tracking wheels to 0.
*/
void resetTrackingWheels();

/*
Sets the drive train motor brakeTypes to coast - used for auton so it'll do some cool stunts.
*/
void setDriveCoast();
/*
Sets the drive train motor brakeTypes to brake - use for driver control
*/
void setDriveBrake();

//DRIVE FUNCTIONS
void setDriveMotors();

void resetDriveEncoders();

//AUTONOMOUS FUNCTIONS
/*
Tells robot to travel along the y-axis, with a target distance in inches, and a integer maxSpeed, range -127 - 127;
*/
void rotate(double targetOrientation, int maxSpeed);

void translate(double targetDistance, double targetTheta,  int maxSpeed);

void translateY(double unitsY, double unitsX, int maxSpeed, double KdAdjust, double KpAdjustX);

void translateX(double distanceX, int maxSpeed);

void rotatePID(double targetAngle, int maxSpeed, double KdAdjust);
