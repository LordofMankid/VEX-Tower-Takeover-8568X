#include "main.h"


///////////////////////////
//GLOBAL VARIABLES
///////////////////////////
const double ARMLENGTH = 16.0;
const double ARM_SLOPE_RATIO = 0.5;

int intakeMotorSpeed;
int armMotorSpeed;
double armHeight;

///////////////////
int intakePower;
int armPower;
int macroPowerArm;


//const double LIFT_INCHES_TICKS = 900/chord length of arm thing;

//HELPER FUNCTIONS
void setArmLift(int power){
  armLift = power;
}

void setIntake(int power){
  intakeRight = power;
  intakeLeft = power;
}

//DRIVER CODE
void setIntakeMotors(){
  intakePower = 127*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) - 127*controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
  setIntake(intakePower);
}

void setArmLift(){
  armLift = armPower;
}
/*
Ties the lift of the slope to buttons R1 and R2
*/
void setMacroMotors(){
  armAngle = armLift.get_position();
  macroPowerArm = 127*controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) - 127*controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
  armPower = 127*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));

  armLift = macroPowerArm+armPower;
  pros::lcd::print(7, "armAngle %i", armAngle);
}

//AUTONOMOUS CODE
