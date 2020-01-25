#include "main.h"

typedef struct position{
double xPosition;
double yPosition;
double angle;
} position;

extern position currPosition;

typedef struct polarCoord{
  double radius;
  double angle;

} polarCoord;

typedef struct rectCoord{
  double x;
  double y;
} rectCoord;

extern rectCoord target;
//HELPER FUNCTIONS -- Functions used in other functions listed here

polarCoord rectToPolar(double x, double y);

rectCoord polarToRect(double r, double theta);


//////
void resetPosition();

void updatePosition(); //main position tracking algorithm

double modulo (double a, double b);

double getXposition(); //gets X position in inches

double getYposition(); //get Y position in inches

double getAngleRad(); //gets orientation in radians

double getAngleDeg(); //gets orientation in degrees
