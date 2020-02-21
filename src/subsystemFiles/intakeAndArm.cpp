#include "main.h"


///////////////////////////
//GLOBAL VARIABLES
///////////////////////////
const double ARMLENGTH = 16.0;
const double ARM_SLOPE_RATIO = 0.5;

int intakeMotorSpeed;
int armMotorSpeed;
double armHeight;
double armTarget;
///////////////////
int intakePower;
int armPower;
int macroPowerArm;
int macroSpeed;

////
//Intake autonomous variables
bool intFirstCycle = true;
bool intakeOn;
int intakeStep;
int targTime;

////
//Arm autonomous variables
bool armFirstCycle = true;
bool armOn;
int armStep;
int targHeight;
int armStopParameter;
int lastArmAngle;
int armAngle;
double currentArmTarget;
int voltageArm;
kPID armPID;
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
  intakePower = 127*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) - 70*controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
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

void startIntake(int targetTime, int speed, int driveStepNumber, int intakeStepNumber){
//checks to see if the drive step is same as the one it was assigned to

    if(intakeStep == intakeStepNumber-1){
    printf("hello\n");
      if(driveStepNumber == driveStep){
        intakeOn = true;
        if(intFirstCycle == true){ //if it is the 1st cycle
          //set the initial time to the current time in ms
          targTime = pros::millis() + targetTime; //set the target to whatever the current time is + the target duration
          printf("ayo target %i", targTime);
          intFirstCycle = false; //says 'ay this is not the 1st cycle anymore'
        }
      }

      if(intakeOn == true){
          setIntake(speed);
          printf("targetTime %i, currTime%i\n", targTime, pros::millis());
          if(pros::millis() >= targTime){
              printf("targetReached");
              intakeStep++;
              intakeOn = false; // turns intake off
              intFirstCycle = true; //prepares for the next cycle
            //intakeStepNumber++; //adds one to the intake step number
            }
          }
      else
            setIntake(0);
      }
    else{
      printf("exited %i\n", intakeOn);
    }
    if(intakeOn == false)
        setIntake(0);
}


void intakeMove(int targetTime, int speed, int driveStepNumber, int intakeStepNumber){
//checks to see if the drive step is same as the one it was assigned to
    if(intakeStep < intakeStepNumber){
      if(driveStepNumber == driveStep){
        intakeOn = true;
        if(intFirstCycle == true){ //if it is the 1st cycle
          //set the initial time to the current time in ms
          targTime = pros::millis() + targetTime; //set the target to whatever the current time is + the target duration
          printf("targetTime %i", targTime);
          intFirstCycle = false; //says 'ay this is not the 1st cycle anymore'
        }
      }
    }
    else
      intakeOn = false;

//checks to see if the target has been reached before

//if the intake is on do the following
  if(intakeOn == true){
    setIntake(speed);

    if(pros::millis() >= targTime){
        printf("targetReached");
        intakeOn = false; // turns intake off
        intFirstCycle = true; //prepares for the next cycle
        driveStep++;
        intakeStep++;
      }
  }
  else{
    setIntake(0);
    printf("intakeStep %i\n", intakeStep);
  }
}




void armMove(int targetAngle, int maxSpeed, int driveStepNumber, int armStepNumber){
  if(armStep == armStepNumber-1){
    if(driveStepNumber == driveStep){
      armOn = true;
      armStopParameter = 0;
      currentArmTarget = targetAngle;
      if(armFirstCycle == true){ //if it is the 1st cycle b
        armFirstCycle = false; //says 'ay this is not the 1st cycle anymore'
      }
    }
    if(armOn == true){
      armAngle = armLift.get_position();
      printf("armAngle %i\n", armAngle-targetAngle);
      voltageArm = 127;
      if(currentArmTarget - armAngle < 0)
        voltageArm = -127;
      setMegaLift(voltageArm);
      setArmLift(voltageArm);
      if(armAngle < 0 && voltageArm < 0)
        setArmLift(0);
      //  printf("hi %f\n", abs(armAngle - currentArmTarget));
      if(abs(armAngle - targetAngle) <= 50){
          printf("armTargetReached\n");
          armStep++;
          driveStep++;
          armOn = false; // turns arm off
          armFirstCycle = true; //prepares for the next cycle
        }
      }
      else{
        setArmLift(0);
        setSlopeLift(0);
      }
  }
//if the armis on do the followin

}
void armDown(){
  armPower = -127;
  setArmLift(armPower);
}

void armStop(){
  armPower = 0;
  setArmLift(armPower);
}

void armTo(double position, int velocity){
    armLift.tare_position();
  while(autonRunning == true && fabs(armTarget - armLift.get_position()) < 5.0){
    armTarget = asin(ARMLENGTH/position)*7*1800/360;
    slopeAngle = slopeLift.get_position();
    slopeLift.move_relative(armTarget*3, velocity);
    armLift.move_relative(armTarget, velocity*88/127);
  //pros::lcd::print(1, "armTarget %f", armTarget);
    pros::delay(10);
  }
}
