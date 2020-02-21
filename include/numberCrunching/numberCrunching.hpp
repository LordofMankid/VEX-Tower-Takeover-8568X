#include "main.h"

//variables
extern double angle;
extern int stepChangeTimes;
//HELPER FUNCTIONS

void nextStep(int stepSet, int time);

/**
Checks if a < b, return 1 if it is
**/
int compareValues(double a, double b);



//CALCULATION FUNCTIONS

rectCoord vectorSummation(rectCoord v1, rectCoord v2);

rectCoord vectorSummation(rectCoord v1, position v2);

double findDistance(rectCoord targetCoord, position position);

double findDistance(position position1, position position2);

/*For use in the PID loop, checks to see if the current position has passed an auton line, return 1 for no, -1 for yes
 @Assumes current orientation is towards the line */
//int targetPass(rectCoord target, position currentPosition, double targetTheta);
int targetPass(rectCoord target, position currentPosition, double targetTheta, position initialPosition, double initialTheta);

int targetRelativePos(rectCoord target, position currentPosition, double initialTheta);

int targetRelativeOrientation(double initialTheta);

int absoluteDirection(rectCoord target, position position, double initialTheta);

int positionReachCheck(position currentPosition, position lastPosition, int driveStopParameter, rectCoord target);
double positionReachCheck(double currentPositionY, double currentPositionX, double lastPositionY, double lastPositionX,  double driveStopParameter, double targetY, double targetX);
/*
Returns a driveStopParameter that is used to exit a PID loop. Checks if there has been a position change, and if there is, then driveStopParameter is reset
*/
int positionReachCheck(double currentPosition, double lastPosition, int motorStopParameter, double target, double marginOfError);
/*
Returns a motorStope parameter used to exit a PID loop.
*/

double adjustKp(double Kpid, double increment);

void printToBrain();

void angleTrack();
