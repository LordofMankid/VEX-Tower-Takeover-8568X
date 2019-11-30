#include "main.h"

//CONSTANTS
const double REG_INCH_TICK = 900/(4*PI);
//HELPER FUNCTIONS

void resetDriveEncoders(){
  FrontLeft.tare_position();
  FrontRight.tare_position();
  BackLeft.tare_position();
  BackRight.tare_position();
}

double avgDriveEncoderValue() {
  return (fabs(FrontLeft.get_position()) +
         fabs(FrontRight.get_position()) +
         fabs(BackLeft.get_position()) +
         fabs(BackRight.get_position())) / 4;
}
//AUTON FUNCTIONS
void translateY_reg(double unitsY, int voltage)
{
  //defines direction based on units provided
  int directionY = fabs(unitsY) / unitsY;
  unitsY = unitsY*REG_INCH_TICK;
  //reset motor encoder and gyro
  resetDriveEncoders();

  //drive forward until units reached
  while(avgDriveEncoderValue() < fabs(unitsY))
  {
    setDriveAuton(unitsY, 0, 0, voltage);
    pros::delay(10);
  }
  //brief brake depending on direction
  setDrive(0, -10 * directionY, 0);
  pros::delay(50);
  //reset drive
  setDrive(0,0,0);
  pros::delay(20);
}
