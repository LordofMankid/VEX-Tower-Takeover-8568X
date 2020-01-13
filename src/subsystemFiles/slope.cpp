#include "main.h"

int voltageSlope;
int slopePower;
double slopeMaxAngle;
double slopeAngle;
int slopeStopParameter;
int percentageSlope;
int macroPower;
int slopeDownPower;
/////////////////////////////////////////////////////////////////
const double slopeThreshold = 35.5;

//HELPER FUNCTIONS
void setSlopeLift(int power){
  slopeLift = power;
}

void setSlopeVelocity(int velocity){
  slopeLift.move_velocity(velocity);
}
//DRIVER CODE
void setSlopeMotors(){
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
    slopeLift.tare_position();
  slopeAngle = slopeLift.get_position();
  voltageSlope = PIDloop(0.05, 0.0, 0.0, 6800, slopeAngle);
  percentageSlope = slopeAngle/slopeMaxAngle;
  if(slopeAngle < 0)
    slopeAngle = 0;

  if(slopeAngle > 2250 && voltageSlope > 0)
    {
        //voltageSlope = 100;
      if(slopeAngle > 3500)
        voltageSlope = 60;
    }
    else
    {
      voltageSlope = PIDloop(0.05, 0.0, 0.0, 6800, slopeAngle);
    }
  if(slopeAngle < 100)
    slopeDownPower = 0;
  else
    slopeDownPower = 127;

  slopePower = voltageSlope*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) - 127*controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

  macroPower = 127*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) - 127*controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
  pros::lcd::print(7, "slope power= %i", slopePower);

  slopeLift = slopePower + macroPower;

}

//AUTONOMOUS CODE

void slopeUp(int targetAngle, int maxSpeed){
  int lastSlopeAngle;
  bool targetReach = false;

  while(autonRunning == true && targetReach == false){
    slopeAngle = slopeLift.get_position();
    voltageSlope = PIDloop(0.05, 0.0, 0.0, targetAngle, slopeAngle);
    slopePower = voltageSlope;
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      autonRunning = false;
    if(slopeAngle > 3250 && slopePower > 127)
      slopePower = maxSpeed;
    if(fabs(slopeAngle) > 6800){
      targetReach = true;
      break;
    }

      setSlopeLift(slopePower);
    pros::lcd::print(1, "slopeAngle = %f", slopeAngle);
//    positionReachCheck(slopeAngle, lastSlopeAngle, slopeStopParameter, targetAngle, 75);
//    lastSlopeAngle = slopeAngle;
  }
}

void slopeDown(int targetAngle){
  slopeAngle = slopeLift.get_encoder_units();
  slopePower = -127;
  if(slopeAngle == targetAngle)
    slopePower = 0;
  setSlopeLift(slopePower);
}
