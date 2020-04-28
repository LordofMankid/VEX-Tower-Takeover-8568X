#include "main.h"

int slopeStopParameter;
double lastSlopeAngle;
bool slopeFirstCycle;
bool slopeOn = true;
int slopeStep = 0;
int currentTarget;

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
      voltageSlope = PIDloop(0.06, 0.0, 0.0, 7000, slopeAngle);
      if(slopeAngle > 3000 && slopeAngle < 6000)
        {
          if(slopeAngle > 3800 && slopeAngle <= 4700)
            voltageSlope = 100;
          if(slopeAngle > 4700)
            voltageSlope = 70;
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
        setSlopeLift(0);
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

  while(targetReach == false){
      slopeAngle = slopeLift.get_position();
      printf("slopeAngle %f", slopeAngle-targetAngle);
      voltageSlope = 127;
      if(slopeAngle > 3000 && slopeAngle < 7000)
        {
          if(slopeAngle > 3800 && slopeAngle <= 4700)
            voltageSlope = 100;
          if(slopeAngle > 4700)
            voltageSlope = 60;
          pros::lcd::print(5, "slope power= %i", voltageSlope);
        }
      else
        voltageSlope = PIDloop(0.05, 0.0, 0.0, 7000, slopeAngle);
      if(targetAngle - slopeAngle < 0){
        voltageSlope = -127;
      }
      lastSlopeAngle = slopeAngle;
      slopeStopParameter = positionReachCheck(slopeAngle, lastSlopeAngle, slopeStopParameter, 6000, 50);
      setSlopeLift(voltageSlope);
      //  printf("hi %f\n", abs(slopeAngle - currentTarget));
      if(abs(slopeAngle - targetAngle) <= 50 || slopeStopParameter > 50){
        printf("slopeTargetReached");
        setSlopeLift(0);
        targetReach = true;
      }
      pros::delay(10);
    }
}


void slopeDown(int targetAngle){
  slopeAngle = slopeLift.get_encoder_units();
  slopePower = -127;
  if(slopeAngle == targetAngle)
    slopePower = 0;
  setSlopeLift(slopePower);
}
