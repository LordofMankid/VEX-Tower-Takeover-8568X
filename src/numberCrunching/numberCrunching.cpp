#include "main.h"



//Toggle Kp kind of thing
bool bButtonHeld = false;
int buttonPressed;
int LeftPressed;
int RightPressed;

////////////////////////////
int placeHolder;
int stepChangeTimes = 0;

void nextStep(int stepSet, int time){
  if(stepChangeTimes == time){
    driveStep = stepSet;
    stepChangeTimes++;
  }
}
//Helper Functions
double findDistance(rectCoord targetCoord, position position){
  if(targetCoord.y < 0)
    return sqrt(pow(targetCoord.y+position.yPosition,2) + pow(targetCoord.x-position.xPosition,2));
  else
    return sqrt(pow(targetCoord.y-position.yPosition,2) + pow(targetCoord.x-position.xPosition,2));
}

double findDistance(position position1, position position2){
  return sqrt(pow(position1.yPosition-position2.yPosition,2) + pow(position1.xPosition-position2.xPosition,2));
}

double getAngle(){
  return angle;
}

int positionReachCheck(position currentPosition, position lastPosition, int driveStopParameter, rectCoord target){
  if(lastPosition.xPosition == currentPosition.xPosition && lastPosition.yPosition == currentPosition.yPosition && fabs(target.x - lastPosition.xPosition) < 1.0 && fabs(target.y - lastPosition.yPosition) < 1.0){
    driveStopParameter += 2;
  }
  if(lastPosition.xPosition == currentPosition.xPosition && lastPosition.yPosition == currentPosition.yPosition ){
    driveStopParameter++;
  }
  if((fabs(lastPosition.xPosition) - fabs(currentPosition.xPosition)) > 5 || (fabs(lastPosition.yPosition) - fabs(currentPosition.yPosition)) > 5)
  {
      driveStopParameter = 0.0;
  }
  return driveStopParameter;

}



//Checks if last position
double positionReachCheck(double currentPositionY, double currentPositionX, double lastPositionY, double lastPositionX,  double driveStopParameter, double targetY, double targetX){

    placeHolder = fabs(targetX - lastPositionX);
    pros::lcd::print(4, "position %f | positionX %f", currentPositionY, currentPositionX);
    pros::lcd::print(5, "targetY %f | targetX %f", targetY, targetX);

    pros::lcd::print(6, "movement %f", lastPositionX - currentPositionX);
    if(fabs(targetX - lastPositionX) > 50)
        pros::lcd::print(7,"X is problem");
    else if(fabs(targetY - lastPositionY) > 50)
        pros::lcd::print(7,"Y is problem");
    pros::lcd::print(7, "wheat %f", driveStopParameter);
  if(lastPositionX == currentPositionX && lastPositionY == currentPositionY && fabs(targetX - lastPositionX) < 100 && fabs(targetY - lastPositionY) < 100){
    driveStopParameter++;
  }
  if(lastPositionX == currentPositionX && lastPositionY ==  currentPositionY && fabs(targetX - lastPositionX) < 500 && fabs(targetY - lastPositionY) < 500){
    driveStopParameter = driveStopParameter + 0.5;
  }
  if((fabs(lastPositionX) - fabs(currentPositionX)) > 5 || (fabs(lastPositionY) - fabs(currentPositionY)) > 5)

  {
      driveStopParameter = 0.0;
  }
  return driveStopParameter;
}

int positionReachCheck(double currentPosition, double lastPosition, int motorStopParameter, double target, double marginOfError){
  if(lastPosition == currentPosition && fabs(target - currentPosition) < marginOfError)
    motorStopParameter++;
  else if(lastPosition != currentPosition)
    motorStopParameter = 0;
    return motorStopParameter;
}

void armHeightTrack(){
  armAngle = armLift.get_position()*TICK_DEG_TORQUE;
  armHeight = ARMLENGTH*sin(armAngle);
}



void printToBrain(){
  //Use this function to look at random things

  pros::lcd::print(3, "angle %f", angle);

}

void toggle(){

}
double adjustKp(double Kpid, double increment){
    //
buttonPressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)+ controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);
    if(buttonPressed != 0 && bButtonHeld == false){
      LeftPressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);
      RightPressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);

      Kpid = (Kpid + increment*(RightPressed-LeftPressed));

      bButtonHeld = true;
      pros::lcd::print(6, "KiDrive %f", Kpid);
    }
    else if(buttonPressed == 0){
      bButtonHeld = false;
    }
  return Kpid;
}
