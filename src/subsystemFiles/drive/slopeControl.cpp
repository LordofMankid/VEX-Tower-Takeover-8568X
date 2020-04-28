#include "main.h"

int voltageSlope;
int macroPower;
int slopePower;
double slopeMaxAngle;
double slopeAngle;
int slopeDownPower = 127;



/////////////////////////////////////////////////////////////////


//HELPER FUNCTIONS
void setSlopeLift(int power){
  slopeLift = power;
}

void setSlopeVelocity(int velocity){
  slopeLift.move_velocity(velocity);
}
//DRIVER CODE
void setSlopeMotors(){

  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1 || slopeLimit.get_value() == 1){
    slopeLift.tare_position();
    slopeDownPower = 0;
  }
  else
    slopeDownPower = 127;
  slopeAngle = slopeLift.get_position();
  pros::lcd::print(5, "slope power= %i", slopeAngle);
  voltageSlope = 127;

  if(slopeAngle > 2500 && slopeAngle < 6300)
    {
        //voltageSlope = 100;
      //if(slopeAngle > 2400 && slopeAngle < 3600)
        //voltageSlope = 60;
      if(slopeAngle > 3600 && slopeAngle <= 5500)
        voltageSlope = 60;
      if(slopeAngle > 5500)
        voltageSlope = 40;


    }
    if(slopeAngle >= 6000)
    {
      voltageSlope = 27;
    }
    slopePower = voltageSlope*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) - slopeDownPower*controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);


  macroPower = 80*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) - slopeDownPower*controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);


  slopeLift = slopePower + macroPower;

}
