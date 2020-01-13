#include "main.h"

//MOTORS

pros::Motor slopeLift(7, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FrontLeft(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BackLeft(3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FrontRight(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BackRight(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeLeft(11, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeRight(10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor armLift(8, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);

//CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//SENSORS
pros::ADIEncoder trackingX('A','B');
pros::ADIEncoder trackingLeft('C','D');
pros::ADIEncoder trackingRight('G','H');

//SETUP VARIABLE

const double RADIUS = 10;
const double RIGHTWHEELDISTANCE = 4.875;
const double LEFTWHEELDISTANCE = 4.875;
const double XWHEELDISTANCE = 4.875;
const double TR_TICK_INCH = (2.75*PI)/TICKS_TRACKING_REV;
const double TR_INCH_TICK = 360/(2.75*PI);
const double TICK_DEG_REG = DEG_CIRCLE/TICKS_REGULAR_REV;
const double TICK_DEG_TORQUE = DEG_CIRCLE/TICKS_TORQUE_REV;




void setUp(){
  //SLOPE
  slopeMaxAngle = ((160.962-45.0)/DEG_CIRCLE)*TICKS_REGULAR_REV*SLOPE_GEAR_RATIO;
  slopeLift.set_brake_mode(MOTOR_BRAKE_HOLD);
  slopeLift.tare_position();

  //ARM AND INTAKE
  intakeRight.set_brake_mode(MOTOR_BRAKE_HOLD);
  intakeLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
  armLift.set_brake_mode(MOTOR_BRAKE_HOLD);
  armMotorSpeed = 88;
  intakeMotorSpeed = 127;

  //DRIVE
  setDriveBrake();
  driveFactor = 1;
  //AUTON - DRIVE
  KpDrive = 0.65; //for rotation
  KdDrive = 0.029; // for rotation
  //KpDrive = 0.65;
  //KdDrive = 0.45;
  KiDrive = 0.005;


  }
