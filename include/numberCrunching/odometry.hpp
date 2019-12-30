#include "main.h"

struct position
{
double xPosition;
double yPosition;
double angle;
};

//HELPER FUNCTIONS -- Functions used in other functions listed here

double modulo (double a, double b);

void updatePosition();

double getXposition(); //gets X position in inches

double getYposition(); //get Y position in inches

double getAngleRad(); //gets orientation in radians

double getAngleDeg(); //gets orientation in degrees
