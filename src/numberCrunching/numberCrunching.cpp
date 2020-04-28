#include "main.h"



//Toggle Kp kind of thing
bool bButtonHeld = false;
int buttonPressed;
int LeftPressed;
int RightPressed;

////////////////////////////
int placeHolder;
int stepChangeTimes = 0;

//Helper Functions
double radModulo(double theta){
  theta += PI;
  while(theta < 0) {
    theta +=2*PI;
  }
  theta = modulo(theta, 2*PI);
  theta -= PI;

  return theta;
}

int compareValues(double a, double b){
  return (a < b ? 1:-1);

}
template <class SomeType>
SomeType sum (SomeType a, SomeType b){
  return sqrt(pow(a.y-b.yPosition,2) + pow(a.x-b.xPosition,2));
}
/*
double findDistance(rectCoord targetCoord, position position){

    return sqrt(pow(targetCoord.y-position.yPosition,2) + pow(targetCoord.x-position.xPosition,2));
}

double findDistance(position position1, position position2){
  return sqrt(pow(position1.yPosition-position2.yPosition,2) + pow(position1.xPosition-position2.xPosition,2));
}*/

rectCoord vectorSummation(rectCoord v1, rectCoord v2){
  rectCoord newVector;
  newVector.y = v1.y + v2.y;
  newVector.x = v1.x + v2.x;

  return newVector;
}

rectCoord vectorSummation(rectCoord v1, position v2){
  rectCoord newVector;
  newVector.y = v1.y + v2.yPosition;
  newVector.x = v1.x + v2.xPosition;

  return newVector;
}


int targetPass(rectCoord target, position currentPosition, double targetTheta, position initialPosition, double initialTheta){
  int passed;
  if(targetRelativePos(target, initialPosition, initialTheta) == 1){
    printf("target in front\n");
    if(targetTheta == PI/2 || targetTheta == -PI/2)
      passed = compareValues(currentPosition.xPosition, target.x);
    else if(targetTheta == 0 || targetTheta == PI || targetTheta == -PI)
      passed = compareValues(currentPosition.yPosition, target.y);
    else{
      double limitLineSlope = -tan(targetTheta);
      printf("limitLineSlope %f\n", limitLineSlope);
      passed = compareValues((currentPosition.yPosition/limitLineSlope - currentPosition.xPosition), (target.y/limitLineSlope - target.x));
    }
  }
  else{
    printf("target behind\n");
    if(targetTheta == PI/2 || targetTheta == -PI/2)
      passed = compareValues(target.x, currentPosition.xPosition);
    else if(targetTheta == 0 || targetTheta == PI || targetTheta == -PI)
      passed = compareValues(target.y, currentPosition.yPosition);
    else{
      double limitLineSlope = -tan(targetTheta);
      printf("limitLineSlope %f\n", limitLineSlope);
      if(limitLineSlope < 0)
        passed = -1*compareValues((target.y/limitLineSlope - target.x), (currentPosition.yPosition/limitLineSlope - currentPosition.xPosition));
      else
        passed = compareValues((target.y/limitLineSlope - target.x), (currentPosition.yPosition/limitLineSlope - currentPosition.xPosition));
    }
  }
  return passed;
}

int targetRelativePos(rectCoord target, position position, double initialTheta){
  int passed;
  if(initialTheta == PI/2 || initialTheta == -PI/2)
    passed = compareValues(position.xPosition, target.x);
  else if(initialTheta == 0 || initialTheta == PI)
    passed = compareValues(position.yPosition, target.y);
  else{
    double currPosSlope = -tan(initialTheta);
    printf("currPosSlope %f\n", currPosSlope);
    if(currPosSlope < 0)
      passed = compareValues((target.y/currPosSlope - target.x), (position.yPosition/currPosSlope - position.xPosition));
    else
      passed = compareValues((position.yPosition/currPosSlope - position.xPosition), (target.y/currPosSlope - target.x));

  }
  return passed;
}

int targetRelativeOrientation(double initialTheta){
  double currPosSlope = tan(initialTheta);
  double minThetaLimit = radModulo(initialTheta-PI/2);
  double maxThetaLimit = radModulo(initialTheta+PI/2);

  if(minThetaLimit < initialTheta < maxThetaLimit)
    return 1; //robot faces forward
  else
    return -1; //target faces backward
}

int absoluteDirection(rectCoord target, position position, double initialTheta){

  printf("target front %i\nfacing target%i\n", targetRelativePos(target, position, initialTheta), targetRelativeOrientation(initialTheta));
  return targetRelativePos(target, position, initialTheta)*targetRelativeOrientation(initialTheta);

}


double getGyroAngle(){
  double angle;
  angle = inertia_sensor.get_rotation();
  angle += 180.0;
  while(angle < 0) {
    angle +=360.0;
  }
  angle = modulo(angle, 360.0);
  angle -= 180.0;

  return angle;
}


void nextStep(int stepSet, int time){
  if(stepChangeTimes == time){
    driveStep = stepSet;
    stepChangeTimes++;
  }
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
  if((fabs(lastPosition.xPosition - currentPosition.xPosition)) > 5 || (fabs(lastPosition.yPosition - currentPosition.yPosition)) > 5)
  {
      driveStopParameter = 0;
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
  if(fabs(fabs(lastPosition)-fabs(currentPosition)) <= 1 && fabs(fabs(currentPosition) - fabs(target)) < marginOfError){
    printf("aaa %f", fabs(fabs(target) - fabs(currentPosition)));
    motorStopParameter++;
  }
  else if(fabs(fabs(lastPosition) - fabs(currentPosition)) > 1){
    motorStopParameter = 0;
  printf("aa %f\n", fabs(fabs(lastPosition) - fabs(currentPosition)));
  }
  printf("aaa %f\n", fabs(target) - fabs(currentPosition));
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
