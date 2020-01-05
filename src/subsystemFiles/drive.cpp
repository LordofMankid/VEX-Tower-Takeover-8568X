#include "main.h"

int leftJoystickY;
int leftJoystickX;
int rightJoystickX;

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
double angleToTarget;


//
//HELPER FUNCTIONS
void setDrive(int yPower, int xPower, int rPower){
  FrontLeft = yPower - xPower + rPower;
  FrontRight = yPower + xPower - rPower;
  BackLeft = yPower + xPower + rPower;
  BackRight = yPower - xPower - rPower;
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
    leftJoystickY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    leftJoystickX = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    rightJoystickX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    //"deadzone" - the absolute value thing
    if(abs(leftJoystickY) < 30 && abs(leftJoystickX) > 50)
      leftJoystickY = 0;
    if(abs(leftJoystickX) < 30 && abs(leftJoystickY) < 50 )
      leftJoystickX = 0;
    if(slopeAngle > slopeThreshold)
      driveFactor = 1;
    else
      driveFactor = 1;
      setDrive(leftJoystickY*driveFactor, leftJoystickX*driveFactor, rightJoystickX*driveFactor);
}

//AUTONOMOUS FUNCTIONS
void translateY(double unitsY, double unitsX, int maxSpeed, double KdAdjust, double KpAdjustX)  //might have to add units X, units Y
{
  //define direction based on units provided
  int directionY = fabs(unitsY) / unitsY;
  int voltageY = 0;
  int voltageX = 0;
  int voltageR = 0;
  int maxErrorX = 0;

  double lastPositionX = 0;
  double lastPositionY = 0;
  double lastPositionA = 0;

  double driveStopTime = 0.0;
  targetReach = false;

  unitsY = unitsY*TR_INCH_TICK;
  unitsX = unitsX*TR_INCH_TICK;

  setDriveCoast();
  resetTrackingWheels();
  //PID loop - drive forward until units reached
  while(targetReach == false) //MAKE SURE TO CHANGE CONDITION LATER
  {
    pros::lcd::print(7, "movement entered");
    //angleTrack();
    positionY = (trackingLeft.get_value() + trackingRight.get_value())/2;
    positionX = trackingX.get_value();
    positionA = angle;
    voltageY = PIDloop(0.65, 0.0075, 0.415 + KdAdjust, unitsY, positionY);
    voltageX = PIDloop(KpAdjustX, 0.000, 0.02, unitsX, positionX);
    voltageR = PIDloop(1.5, 0.0, 0.0, 0.1, positionA);

    if(abs(voltageY) > maxSpeed)
      voltageY = maxSpeed*directionY;

    driveStopTime = positionReachCheck(positionY, positionX, lastPositionY, lastPositionX, driveStopTime, unitsY, 0.0);

    lastPositionX = positionX; //"saves" the last recorded position to compare with the next one0
    lastPositionY = positionY;
    lastPositionA = positionA;
    if(driveStopTime >= 25){
        pros::lcd::print(2, "targetError %f", fabs(unitsY)-fabs(positionY));
        targetReach = true;
    }

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) ==1){
      pros::lcd::print(2, "targetError %f", unitsY-voltageY);
      targetReach = true;
    }

    //prints PID values and max error value?
    pros::lcd::print(3, "driveStopTime %f", driveStopTime);


    setDrive(voltageY, voltageX, voltageR); //TODO: convert voltage units into mV
    pros::delay(10);
  }
  //reset drive
  setDrive(0,0,0);
  pros::delay(20);

}

void translateX(double unitsX, int maxSpeed)  //might have to add units X, units Y
{

    //define direction based on units provided
    int directionX = fabs(unitsX) / unitsX;
    int voltageY = 0;
    int voltageX = 0;
    int voltageR = 0;
    int maxErrorX = 0;
    angle = 0;
    double lastPositionX = 0;
    double lastPositionY = 0;
    double lastPositionA = 0;

    double driveStopTime = 0.0;
    targetReach = false;
    unitsX = unitsX*TR_INCH_TICK;
    setDriveCoast();
    resetTrackingWheels();
    //PID loop - drive forward until units reached
    while(autonRunning == true && targetReach ==false) //MAKE SURE TO CHANGE CONDITION LATER
    {
      angleTrack();
      positionY = (trackingLeft.get_value() + trackingRight.get_value())/2;
      positionX = trackingX.get_value();
      positionA = angle;
      voltageY = PIDloop(0.50, 0.0, 0.27, 0.0, positionY);
      voltageX = PIDloop(0.65, 0.0, 0.45, unitsX, positionX);
      voltageR = PIDloop(1.5, 0.0, 0.0045, 0.00, positionA);

      if(abs(voltageY) > maxSpeed)
        voltageY = maxSpeed;

      if(fabs(positionX) >= fabs(lastPositionX))
        maxErrorX = voltageX;

      driveStopTime = positionReachCheck(positionY, positionX, positionY,lastPositionX, driveStopTime, 0.0, unitsX);
      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1){
          printf("yeet %f", unitsX-voltageX);
          autonRunning = false;
      }
      if(driveStopTime > 25){
      pros::lcd::print(2, "thing reached, %f", positionX-unitsX);
      targetReach = true;
      }

      //prints PID values and max error value?


      setDrive(voltageY, voltageX, voltageR); //TODO: convert voltage units into mV
      lastPositionX = positionX; //"saves" the last recorded position to compare with the next one
      lastPositionY = positionY;
      lastPositionA = positionA;
      pros::delay(10);
    }
    //reset drive
    setDrive(0,0,0);
    pros::delay(20);
}

void translate(double targetDistance, double targetTheta, double targetOrientation, int maxSpeed){

  if(targetOrientation < 0)
    turnDirection = -1;
  else
    turnDirection = 1;

  // newAngle = targetOrientation + position.angle;  //use if you figure out a way to run this only once

  angleToTarget = targetOrientation - getAngleDeg();

  voltageY = PIDloop(0.75, 0.0, 0.5, cos(turnDirection*(fabs(targetTheta+angleToTarget)-90))*targetDistance, position.yPosition);
  voltageX = PIDloop(0.75, 0.0, 0.5, sin(turnDirection*(fabs(targetTheta+angleToTarget)-90))*targetDistance, position.xPosition);
  voltageR = PIDloop(0.75, 0.0, 0.5, targetOrientation, getAngleDeg());

  if(abs(voltageY) > maxSpeed)
    voltageY = maxSpeed;
  if(abs(voltageX) > maxSpeed)
    voltageX = maxSpeed;
  if(abs(voltageR) > maxSpeed)
    voltageR = maxSpeed;

  setDrive(voltageY, voltageX, voltageR);
  /*double directionY;
  double directionX;
  int voltageY = 0;
  int voltageX = 0;
  int voltageR = 0;
  int maxErrorX = 0;

  double lastPositionX = 0.0;
  double lastPositionY = 0.0;
  double lastPositionA = 0.0;
  targetReach = false;
  if(directionY < 0)
    directionY = -1;
  if(directionX < 0)
    directionX = -1;
  int driveStopTime = 0;
  while(autonRunning == true && targetReach == false) //MAKE SURE TO CHANGE CONDITION LATER

  {
    //angleTrack();
    positionY = (trackingLeft.get_value() + trackingRight.get_value())/2;
    positionX = trackingX.get_value();
    positionA = angle;
    voltageY = PIDloop(0.75, 0.0, 0.5, unitsY, positionY);
    voltageX = PIDloop(0.5, 0.0, 0.1, unitsX, positionX);
    voltageR = PIDloop(1.75, 0.0005, 0.0045, 0.00, positionA);

    if(abs(voltageY) > maxSpeed)
      voltageY = maxSpeed;

    if(fabs(positionX) >= fabs(lastPositionX))
      maxErrorX = voltageX;

    positionReachCheck(lastPositionX, lastPositionY, positionY, positionX, driveStopTime, unitsY, unitsX);

    //prints PID values and max error value?
    pros::lcd::print(3, "Y sensor PID 2.0 = %i", voltageY);
    pros::lcd::print(4, "X sensor PID 2.0 = %i | X maximum error:%i", voltageX  , maxErrorX);
    setDrive(voltageY, voltageX*directionX, angle); //TODO: convert voltage units into mV
    lastPositionX = positionX; //"saves" the last recorded position to compare with the next one
    lastPositionY = positionY;
    lastPositionA = positionA;
    pros::delay(10);
  }*/
  //reset drive
  //setDrive(0,0,0);
  //pros::delay(20);
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
    setDrive(voltageY, voltageX, voltageR );

    lastPositionX = positionX; //"saves" the last recorded position to compare with the next one
    lastPositionY = positionY;
    lastPositionA = positionA;
    pros::delay(10);
  }
  //reset drive
  setDrive(0,0,0);
  pros::delay(20);

}
