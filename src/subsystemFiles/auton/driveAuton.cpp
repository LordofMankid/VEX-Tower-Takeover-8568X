#include "main.h"

double positionY;
double positionX;
double positionA;

int driveFactor;
bool targetReach;
double KpDrive;
double KdDrive;
double KiDrive;

//
int turnDirection;
int voltageY;
int voltageR;
int voltageX;

double newDistance;
double newAngle;
double targetOrientation;

bool firstCycle = true;
bool atanAdjust = false;
bool turnClockwise = true;
int targetReached;
int driveStep = 0;
int autonDirection;
int limitPass;
position lastPosition;

double lastTargetAngle;
position initialPosition;
double distanceFromInitial;
double initTargetDistance;
double lastOrientation;
double correctionThreshold;

//rectCoord relTarget;
rectCoord absTarget;
rectCoord lastTarget;
//

void autoTranslate(double targetDistance, int targetSpeed, int maxTime){
  FrontLeft.move_absolute(targetDistance*REG_INCH_TICK, targetSpeed);
  FrontRight.move_absolute(targetDistance*REG_INCH_TICK, targetSpeed);
  BackLeft.move_absolute(targetDistance*REG_INCH_TICK, targetSpeed);
  BackRight.move_absolute(targetDistance*REG_INCH_TICK, targetSpeed);
  while(!((FrontLeft.get_position() < (targetDistance + 0.1)*REG_INCH_TICK) && (FrontLeft.get_position() > (targetDistance - 0.1)*REG_INCH_TICK))){
    updatePosition();
    delayStep++;
    if(delayStep > maxTime/10){
      delayStep = 0;
      break;
    }
    pros::delay(10);
  }
}

void translate(double targetDistance, double targetTheta, double endingOrientation, int maxSpeed, int driveStepNumber){

  if(driveStep == driveStepNumber){
    if(firstCycle == true){
      rectCoord relTarget;
      //printf("kP %f", forwardPID.kP);
      initialPosition = currPosition;

      relTarget = polarToRect(targetDistance, (targetTheta+endingOrientation)*PI/180);
      printf("last Y %f\n last X%f\n", lastTarget.y, lastTarget.x);
      absTarget = vectorSummation(relTarget, lastTarget);
      initTargetDistance = targetDistance;
      autonDirection = fabs(targetDistance)/targetDistance;
      if(absTarget.y < initialPosition.yPosition){
          atanAdjust = true;
          printf("yes backward");
      }
      else
        atanAdjust = false;
      firstCycle = false;
      //autonDirection = absoluteDirection(absTarget, initialPosition, initialPosition.angle);
      correctionThreshold = 5000;
      printf("initX %f\n init Y %f\n", relTarget.x, relTarget.y);
    }

    limitPass = targetPass(absTarget, currPosition, endingOrientation*DEG_RAD, initialPosition, initialPosition.angle);
    printf("targetPassed %i\nautonDirection %i\n", limitPass, autonDirection);

    printf("X %f\n Y%f\n", absTarget.x, absTarget.y);

    printf("X %f\n Y%f\n", currPosition.xPosition, currPosition.yPosition);

    //Finds the distance from the initial point
    //distanceFromInitial = findDistance(initialPosition, currPosition);
    //Finds the target orientation and converts the sign as necessary, 0 degrees being forward
    if(autonDirection > 0){
      targetOrientation = PI/2 - atan2(absTarget.y-currPosition.yPosition, absTarget.x-currPosition.xPosition);
    }
    else
      targetOrientation = 3*PI/2 - atan2(absTarget.y-currPosition.yPosition, absTarget.x-currPosition.xPosition);


    if(targetOrientation >= PI)
      targetOrientation -= 2*PI;
    else if(targetOrientation <= -PI)
      targetOrientation += 2*PI;

      //Sets the PID loop
    voltageY = PIDdrive(forwardPID, targetDistance, findDistance(absTarget, currPosition));

    if(findDistance(absTarget, currPosition)*1000 < correctionThreshold){
      double correctedOrientation;
      correctedOrientation = (findDistance(absTarget, currPosition)/correctionThreshold*targetOrientation*180/PI) + (1-(findDistance(absTarget, currPosition)/correctionThreshold))*endingOrientation;
      printf("distance to target: %f \nnew targetAngle %f\nangle %f\n", findDistance(absTarget, currPosition), correctedOrientation, getAngleDeg());
      voltageR = PIDloop(adjustPID, correctedOrientation, getAngleDeg());
    }
    else
      voltageR = PIDloop(adjustPID, targetOrientation*180/PI, getAngleDeg());

      printf("target angle: %f\n angle %f\n", targetOrientation*180/PI, currPosition.angle*180/PI);

    //printf("target angle %f \nvoltageR %i\ndistFromSts %f\nvoltageY %i\n", targetOrientation*180/PI, voltageR, distanceFromInitial, voltageY);

    //Sets limit to speed as necessary
    if(abs(voltageY) > maxSpeed)
      voltageY = voltageY/abs(voltageY)*maxSpeed;
    if(abs(voltageR) > maxSpeed)
      voltageR = voltageR/abs(voltageR)*maxSpeed;
    //printf("voltageY %i\nkP %f\nkI %f\nkD %f\n", voltageY, forwardPID.kP, forwardPID.kI, forwardPID.kD);
    printf("distanceLeft %f\n", findDistance(absTarget, currPosition));
    //Sets the drive
    setDrive(voltageY, voltageR);

    //Checks if target is reached
    targetReached = positionReachCheck(currPosition, lastPosition, targetReached, absTarget);

    //Updates last position to compare for next cycle
    lastPosition = currPosition;

    //Resets for next step if target is reached
    if(targetReached > 10){
      setDrive(0,0);
      driveStep++;
      firstCycle = true;
      targetReached = 0;
      limitPass = 1;
      lastTarget = absTarget;
    }
  }

}

void rotate(double targetOrientation, int maxSpeed, int driveStepNumber){

  if(driveStep == driveStepNumber){
    if(firstCycle == true){
      if(targetOrientation < 0)
        turnClockwise = true;
      else
        turnClockwise = false;
      firstCycle = false;

    }
    voltageR = PIDloop(turnPID, targetOrientation, getAngleDeg());
    if(abs(voltageR) > maxSpeed)
      voltageR = voltageR/abs(voltageR)*maxSpeed;
    printf("voltageR %i\n", voltageR);

    setDrive(0, voltageR);

    targetReached = positionReachCheck(getAngleDeg(), lastOrientation, targetReached, targetOrientation, 25.0);

    lastOrientation = getAngleDeg();
    if(targetReached > 10){
      setDrive(0,0);
      driveStep++;
      firstCycle = true;
      targetReached = 0;
      lastTarget.y = currPosition.yPosition;
      lastTarget.x = currPosition.xPosition;
    }

  }

}

void gyroTurn(double targetAngle, int maxSpeed){
  double realTarget;
  realTarget = targetAngle + lastTargetAngle;
  realTarget += 180;
  while(realTarget < 0) {
      realTarget +=360.0;
    }
  realTarget = modulo(realTarget, 360.0);

  realTarget -= 180;
  bool autonRunning = true;

  setDriveCoast();
  while(autonRunning == true){
    voltageR = turnLoop(turnPID, realTarget, getGyroAngle());
    if(abs(voltageR) > maxSpeed)
      voltageR = voltageR/abs(voltageR)*maxSpeed;
    printf("voltageR %i\n", voltageR);

    printf("last Target %f\n", lastTargetAngle);
    setDrive(0, voltageR);

    targetReached = positionReachCheck(getGyroAngle(), lastOrientation, targetReached, realTarget, 5.0);

    lastOrientation = getGyroAngle();
    if(targetReached > 10){
      setDrive(0,0);
      targetReached = 0;
      lastTargetAngle += targetAngle;
      printf("targetReached");
      break;
    }
    pros::delay(10);
  }
}



void rotatePID(double targetAngle, int maxSpeed, double KdAdjust){
  //define direction based on units provided
  int directionR = fabs(targetAngle) / targetAngle;
  int voltageY = 0;
  int voltageX = 0;
  int voltageR = 0;
  int count = 0;
  int maxErrorX = 0;
  double lastPositionX = 0;
  double lastPositionY = 0;
  double lastPositionA = 0;
  double driveStopTime = 0;
  targetReach = false;
  //PID loop - drive forward until units reached
  while(autonRunning == true && targetReach == false) //MAKE SURE TO CHANGE CONDITION LATER
  {
    count++;
    //angleTrack();
    positionY = (trackingLeft.get_value()+trackingRight.get_value()/2);
    positionX = trackingX.get_value();
    positionA = angle;

    voltageY = PIDloop(0.0, 0.0, 0.0, 0.0, positionY);
    voltageX = PIDloop(0.0, 0.0, 0.0, 0.0, positionX);
    voltageR = PIDloop(1.75, 0.0, 0.0045+KdAdjust, targetAngle, positionA);
    pros::lcd::print(1, "voltage %i, count %i", voltageR, count);
    if(voltageR > maxSpeed)
      voltageR = maxSpeed;

    driveStopTime = positionReachCheck(positionA, lastPositionA, driveStopTime, targetAngle, 10);
      if(driveStopTime >= 25)
        targetReach = true;
      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
        pros::lcd::print(5, "error &f", targetAngle-positionA);
        autonRunning = false;
      }
    //prints PID values and max error value?
    pros::lcd::print(3, "angle %f", positionA);
    pros::lcd::print(4, "distanceLeft %f", targetAngle-positionA);
    setDrive(voltageY,  voltageR );

    lastPositionX = positionX; //"saves" the last recorded position to compare with the next one
    lastPositionY = positionY;
    lastPositionA = positionA;
    pros::delay(10);
  }
  //reset drive
  setDrive(0,0);
  pros::delay(20);

}
