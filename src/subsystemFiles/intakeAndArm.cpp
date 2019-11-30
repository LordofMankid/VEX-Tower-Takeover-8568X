#include "main.h"


///////////////////////////
//GLOBAL VARIABLES
///////////////////////////
const double ARMLENGTH = 16.0;
const double ARM_SLOPE_RATIO = 0.5;
int armAngle;
int intakeMotorSpeed;
int armMotorSpeed;
double armHeight;
double armTarget;
///////////////////
int intakePower;
int armPower;
int macroPowerArm;
int macroSpeed;

//const double LIFT_INCHES_TICKS = 900/chord length of arm thing;

//HELPER FUNCTIONS
void setArmLift(int power){
  armLift = power;
}

void setIntake(int power){
  intakeRight = power;
  intakeLeft = power;
}

void setMegaLift(int power){
    armLift = power;
    slopeLift = power;
}
//DRIVER CODE
void setIntakeMotors(){
  intakePower = intakeMotorSpeed*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1));
  setIntake(intakePower);
}

void setArmMotor(){
  armLift = armPower;
}
/*
Ties the lift of the slope to buttons R1 and R2
*/
void setMacroMotors(){
  macroPowerArm = 88*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
  armPower = armMotorSpeed*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y));

  armLift = macroPowerArm+armPower;
  pros::lcd::print(7, "macropower %i", macroPowerArm);
}

//AUTONOMOUS CODE

void intakeIn(){
  intakePower = -125;
  setIntake(intakePower);
}

void intakeOut(){
  intakePower = 127;
  setIntake(intakePower);
}

void intakeStop(){
  intakePower = 0;
  setIntake(intakePower);
}

void armUp(){
  armPower = 127;
  setArmLift(armPower);
}

void armDown(){
  armPower = -127;
  setArmLift(armPower);
}

void armStop(){
  armPower = 127;
  setArmLift(armPower);
}

void armTo(double position, int velocity){
    armLift.tare_position();
  while(autonRunning == true && fabs(armTarget - armLift.get_position()) < 5.0){
    armTarget = asin(ARMLENGTH/position)*7*1800/360;
    slopeAngle = slopeLift.get_position();
    slopeLift.move_relative(armTarget*3, velocity);
    armLift.move_relative(armTarget, velocity*88/127);
    pros::lcd::print(1, "armTarget %f", armTarget);
    pros::delay(10);
  }
}
