#include "main.h"

//variables
extern double angle;
extern int stepChangeTimes;
//HELPER FUNCTIONS

void nextStep(int stepSet, int time);

//CALCULATION FUNCTIONS

rectCoord vectorSummation(rectCoord v1, rectCoord v2);

rectCoord vectorSummation(rectCoord v1, position v2);

double findDistance(rectCoord targetCoord, position position);

double findDistance(position position1, position position2);


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
