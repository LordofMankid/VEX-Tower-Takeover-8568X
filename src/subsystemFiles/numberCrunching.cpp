#include "main.h"

float error;
float integral = 0;
float derivative;
float prevError = 0;
const int integralMax = 25;

////////
//NumberCrunchingVariables
double positionL;
double positionR;

double initL = 0.0;
double initR = 0.0;

double lastPositionL;
double lastPositionR;

double deltaL;
double deltaR;

double initAngle = 0.0;
double lastAngle;
double angle;

double dAngle;
/////////////////////////
//Toggle Kp kind of thing
bool bButtonHeld = false;
int buttonPressed;
int LeftPressed;
int RightPressed;
////////////////////////////
int placeHolder;


//Helper Functions

double getAngle(){
  return angle;
}

//This PID loop returns just a number value - the value that the voltage needs to be. This is so that you can use this PIDloop function in a number of different usages.
int PIDloop(float Kp, float Ki, float Kd, double units, double EncoderValue){
  int voltage;

  //sets error
  error = units - EncoderValue;
  pros::lcd::print(0, "error: %f, %f, %f", error, units, EncoderValue);
  //increases error based on time taken to reach target - if resistance is encountered then integral will increase
  integral = integral + error;
  //resets integral if place is reached
  if(error == 0)
    integral = 0;
  //reset integral if it becomes super big
  if(fabs(error) >= integralMax)
    integral = 0;
  derivative = prevError - error; //finds derivative of errors
  prevError = error; //updates prevError
  //set voltage to equal the error
  voltage = (error*Kp) + (integral*Ki) + (derivative*Kd);
  if(voltage > 127)
    voltage = 127;
  if(voltage < -127)
    voltage = -127;

  return voltage;
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

void angleTrack(){
  positionL = trackingLeft.get_value()*TR_TICK_INCH;
  positionR = trackingRight.get_value()*TR_TICK_INCH;
  placeHolder = trackingX.get_value()*TR_TICK_INCH;
  deltaL = positionL - initL;
  deltaR = positionR - initR;

  angle = initAngle + (deltaL-deltaR)/(RIGHTWHEELDISTANCE+LEFTWHEELDISTANCE);

  lastPositionL = positionL;
  lastPositionR = positionR;
  lastAngle = angle;

  angle = angle*180.0/PI;
  printToBrain();
}

void printToBrain(){
  //Use this function to look at random things
  pros::lcd::print(5, "dL %f", positionL);
  pros::lcd::print(4, "dR %f", trackingX.get_value()*TR_TICK_INCH);
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
