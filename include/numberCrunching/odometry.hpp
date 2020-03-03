#include "main.h"

/*
The robot's global X-Y position on the field according to odometry, with the starting point being the origin.

Members:
xPosition - position along the global X-axis in inches
yPosition - position along the global Y-axis in inches
angle - a bearing from the global Y-axis in radians, between -PI and PI

*/
typedef struct position{
double xPosition;
double yPosition;
double angle;
} position;

/*
Polar coordinates for the field

radius - distance, p
angle - angle

*/
typedef struct polarCoord{
  double radius;
  double angle;

} polarCoord;

typedef struct rectCoord{
  double x;
  double y;
} rectCoord;

extern position currPosition;
//HELPER FUNCTIONS -- Functions used in other functions listed here

polarCoord rectToPolar(double x, double y);

rectCoord polarToRect(double r, double theta);


//////
void resetPosition();

void updatePosition(); //main position tracking algorithm

double modulo (double a, double b);

double godulo(double a, double b);
double getXposition(); //gets X position in inches

double getYposition(); //get Y position in inches

double getAngleRad(); //gets orientation in radians

double getAngleDeg(); //gets orientation in degrees
