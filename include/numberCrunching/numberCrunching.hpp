#include "main.h"

//variables
extern double angle;
//HELPER FUNCTIONS

//CALCULATION FUNCTIONS


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