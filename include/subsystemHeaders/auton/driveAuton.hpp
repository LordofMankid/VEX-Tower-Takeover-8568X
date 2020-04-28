#include "main.h"

void autoTranslate(double targetDistance, int targetSpeed, int maxTime);
/*
Tells robot to travel along the y-axis, with a target distance in inches, and a integer maxSpeed, range -127 - 127;
*/
void translate(double targetDistance, double targetTheta, double endingOrientation, int maxSpeed, int driveStepNumber);


void translate(double targetDistance, double targetTheta,  int maxSpeed);


void rotate(double targetOrientation, int maxSpeed, int driveStepNumber);

void rotate(double targetOrientation, int maxSpeed);

void gyroTurn(double targetAngle, int maxSpeed);

void rotatePID(double targetAngle, int maxSpeed, double KdAdjust);
