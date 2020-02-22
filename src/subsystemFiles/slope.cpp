#include "main.h"

int voltageSlope;
int slopePower;
double slopeMaxAngle;
double slopeAngle;
int slopeStopParameter;
int macroPower;
int slopeDownPower = 127;

double lastSlopeAngle;
bool slopeFirstCycle;
bool slopeOn = true;
int slopeStep = 0;
int currentTarget;

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

  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1 || slopeLimit.get_value() == 1){
    slopeLift.tare_position();
    slopeDownPower = 0;
  }
  else
    slopeDownPower = 127;
  slopeAngle = slopeLift.get_position();
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

      pros::lcd::print(5, "slope power= %i", voltageSlope);
    }
    if(slopeAngle >= 6300)
    {
      voltageSlope = 30;
    }
    slopePower = voltageSlope*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) - slopeDownPower*controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);


  macroPower = 80*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) - slopeDownPower*controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);


  slopeLift = slopePower + macroPower;

}

//AUTONOMOUS CODE

void startSlopeMove(int targetAngle, int maxSpeed, int driveStepNumber, int slopeStepNumber){
  if(slopeStep == slopeStepNumber-1){
    if(driveStepNumber == driveStep){
      slopeOn = true;
      slopeStopParameter = 0;
      currentTarget = targetAngle;
      if(slopeFirstCycle == true){ //if it is the 1st cycle b
        slopeFirstCycle = false; //says 'ay this is not the 1st cycle anymore'
      }
    }

//printf("slopeStep %i\n", slopeStep);
    if(slopeOn == true){
      slopeAngle = slopeLift.get_position();
      printf("slopeAngle %f", slopeAngle-targetAngle);
      voltageSlope = PIDloop(0.05, 0.0, 0.0, 6000, slopeAngle);
      if(slopeAngle > 3000 && slopeAngle < 6000)
        {
          if(slopeAngle > 3800 && slopeAngle <= 4700)
            voltageSlope = 52;
          if(slopeAngle > 4700)
            voltageSlope = 40;
          pros::lcd::print(5, "slope power= %i", voltageSlope);
        }
      else
        voltageSlope = PIDloop(0.05, 0.0, 0.0, 6000, slopeAngle);
      if(currentTarget - slopeAngle < 0){
        voltageSlope = -127;
      }
      lastSlopeAngle = slopeAngle;
      slopeStopParameter = positionReachCheck(slopeAngle, lastSlopeAngle, slopeStopParameter, 6000, 50);
      setSlopeLift(voltageSlope);
      //  printf("hi %f\n", abs(slopeAngle - currentTarget));
      if(abs(slopeAngle - targetAngle) <= 50 || slopeStopParameter > 50){
        printf("slopeTargetReached");
        slopeStep++;
        slopeOn = false; // turns slope off
        slopeFirstCycle = true; //prepares for the next cycle
      }
    }
    else
      setSlopeLift(0);
  }
}

void slopeMove(int targetAngle, int maxSpeed, int driveStepNumber, int slopeStepNumber){
  if(slopeStep == slopeStepNumber-1){
    if(driveStepNumber == driveStep){
      slopeOn = true;
      slopeStopParameter = 0;
      currentTarget = targetAngle;
      if(slopeFirstCycle == true){ //if it is the 1st cycle b
        slopeFirstCycle = false; //says 'ay this is not the 1st cycle anymore'
      }
    }

//printf("slopeStep %i\n", slopeStep);
    if(slopeOn == true){
      slopeAngle = slopeLift.get_position();
      printf("slopeAngle %f", slopeAngle-targetAngle);
      voltageSlope = PIDloop(0.05, 0.0, 0.0, 6000, slopeAngle);
      if(slopeAngle > 3000 && slopeAngle < 6000)
        {
          if(slopeAngle > 3800 && slopeAngle <= 4700)
            voltageSlope = 52;
          if(slopeAngle > 4700)
            voltageSlope = 40;
          pros::lcd::print(5, "slope power= %i", voltageSlope);
        }
      else
        voltageSlope = PIDloop(0.05, 0.0, 0.0, 6000, slopeAngle);
      if(currentTarget - slopeAngle < 0){
        voltageSlope = -127;
      }
      lastSlopeAngle = slopeAngle;
      slopeStopParameter = positionReachCheck(slopeAngle, lastSlopeAngle, slopeStopParameter, 6000, 50);
      setSlopeLift(voltageSlope);
      //  printf("hi %f\n", abs(slopeAngle - currentTarget));
      if(abs(slopeAngle - targetAngle) <= 50 || slopeStopParameter > 50){
        printf("slopeTargetReached");
        slopeStep++;
        driveStep++;
        slopeOn = false; // turns slope off
        slopeFirstCycle = true; //prepares for the next cycle
      }
    }
    else
      setSlopeLift(0);
  }
}

void slopeMoveTest(int targetAngle, int maxSpeed, int driveStepNumber, int slopeStepNumber){
  if(slopeStep == slopeStepNumber - 1){
    if(driveStepNumber == driveStep){
      slopeOn = true;
      slopeStopParameter = 0;
      currentTarget = targetAngle;

    if(slopeFirstCycle == true){ //if it is the 1st cycle b
        slopeFirstCycle = false; //says 'ay this is not the 1st cycle anymore'
      }
    }

    if(slopeOn == true){
      slopeAngle = slopeLift.get_position();
      if(slopeAngle > 3000 && slopeAngle < 6000)
        {
          voltageSlope = PIDloop(0.05, 0.0, 0.0, 6000, slopeAngle);
          if(slopeAngle > 3800 && slopeAngle <= 4700)
            voltageSlope = 52;
          if(slopeAngle > 4700)
            voltageSlope = 40;
          pros::lcd::print(5, "slope power= %i", voltageSlope);
        }
      else
        voltageSlope = PIDloop(0.05, 0.0, 0.0, 6000, slopeAngle);
      if(currentTarget - slopeAngle < 0){
        voltageSlope = -127;
      }
      lastSlopeAngle = slopeAngle;
      slopeStopParameter = positionReachCheck(slopeAngle, lastSlopeAngle, slopeStopParameter, 6000, 50);
      setSlopeLift(voltageSlope);
      //  printf("hi %f\n", abs(slopeAngle - currentTarget));
      if(abs(slopeAngle - targetAngle) <= 50 || slopeStopParameter > 50){
          printf("slopeAngle %f", slopeAngle-targetAngle);
          slopeStep++;
          driveStep++;
          slopeOn = false; // turns slope off
          slopeFirstCycle = true; //prepares for the next cycle
        }
      }
      else
      setSlopeLift(0);


  }
  else
    slopeOn = false;

//printf("slopeStep %i\n", slopeStep);
//if the slopeis on do the following

}


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
}
      setSlopeLift(slopePower);
    pros::lcd::print(1, "slopeAngle = %f", slopeAngle);
//    positionReachCheck(slopeAngle, lastSlopeAngle, slopeStopParameter, targetAngle, 75);
//    lastSlopeAngle = slopeAngle;
}


void slopeDown(int targetAngle){
  slopeAngle = slopeLift.get_encoder_units();
  slopePower = -127;
  if(slopeAngle == targetAngle)
    slopePower = 0;
  setSlopeLift(slopePower);
}
