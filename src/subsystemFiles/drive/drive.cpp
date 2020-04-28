#include "main.h"

int drive_yPower;
int drive_xPower;
int drive_rPower;

//HELPER FUNCTIONS
void setDrive(int yPower, int rPower){
  FrontLeft = yPower + rPower;
  FrontRight = yPower - rPower;
  BackLeft = yPower + rPower;
  BackRight = yPower - rPower;
}

void setDriveAuton(double yDistance, double xDistance, double rDistance, int power){
  FrontLeft.move_absolute(yDistance + xDistance + rDistance, power);
  FrontRight.move_absolute(-yDistance + xDistance + rDistance, power);
  BackLeft.move_absolute(yDistance - xDistance + rDistance, power);
  BackRight.move_absolute(-yDistance - xDistance + rDistance, power);
}

void setDriveCoast(){
  FrontLeft.set_brake_mode(MOTOR_BRAKE_COAST);
  FrontRight.set_brake_mode(MOTOR_BRAKE_COAST);
  BackRight.set_brake_mode(MOTOR_BRAKE_COAST);
  BackLeft.set_brake_mode(MOTOR_BRAKE_COAST);
}

void setDriveBrake(){
  FrontLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);
  FrontRight.set_brake_mode(MOTOR_BRAKE_BRAKE);
  BackRight.set_brake_mode(MOTOR_BRAKE_BRAKE);
  BackLeft.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void resetTrackingWheels(){
  trackingLeft.reset();
  trackingRight.reset();
  trackingX.reset();
}


//DRIVE FUNCTIONS
void setDriveMotors(){
    drive_yPower = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    drive_rPower = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    //"deadzone" - the absolute value thing
/*
    if(abs(drive_yPower) < 30 && abs(drive_xPower) > 50)
      drive_yPower = 0;
    if(abs(drive_xPower) < 30 && abs(drive_yPower) < 50 )
      drive_xPower = 0;
*/
      setDrive(drive_yPower, drive_rPower);
}
