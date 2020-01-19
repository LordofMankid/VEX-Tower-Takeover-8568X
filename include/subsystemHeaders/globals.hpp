#include "main.h"

//setup motors
extern pros::Motor slopeLift;
extern pros::Motor FrontLeft;
extern pros::Motor FrontRight;
extern pros::Motor BackLeft;
extern pros::Motor BackRight;
extern pros::Motor intakeLeft;
extern pros::Motor intakeRight;
extern pros::Motor slopeLift;
extern pros::Motor armLift;

//setup sensors
extern pros::Controller controller;
extern pros::ADIEncoder trackingX;
extern pros::ADIEncoder trackingLeft;
extern pros::ADIEncoder trackingRight;

//odom constants
  //Used as conversion factor, for degrees in a circle
  #define DEG_CIRCLE 360.0

  //Conversion Factor, with 360 ticks per revolution for a tracking wheel.
  #define TICKS_TRACKING_REV 360.0

  //Conversion factor, 900 ticks per revolution for a regular V5 motor encoder.
  #define TICKS_REGULAR_REV 900.0

  //Conversion factor, 1800 ticks per revolution for a regular V5 torque encoder.
  #define TICKS_TORQUE_REV 1800.0

  //Sets PI
  //#define PI 3.1415926535

  extern const double RADIUS;

  /*
  Defines the measurement between the right tracking wheel and the tracking center of the robot.
  */
  extern const double RIGHTWHEELDISTANCE;
  /*
  Defines the measure between the left tracking wheel and the tracking center of the robot.
  */
  extern const double LEFTWHEELDISTANCE;
  /*
  Defines the measure between the horizontal tracking wheel and the tracking center of the robot.
  */
  extern const double XWHEELDISTANCE;



/*
Conversion factor for tracking wheels - converts the recorded ticks (in degrees) to inches. Used for calculated distance traveled in inches.
*/
extern const double TR_TICK_INCH;
extern const double TR_INCH_TICK;

//Conversion factor, turning encoder ticks to degrees for regular (18) motors.
extern const double TICK_DEG_REG;

//Conversion factor, turning encoder ticks to degrees for torque motors.
extern const double TICK_DEG_TORQUE;

//setup environment

void setUp();

void tare_motors();
