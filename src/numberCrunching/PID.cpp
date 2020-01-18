#include "main.h"

float error;
float integral = 0;
float derivative;
float prevError = 0;
const int integralMax = 25;

kPID testPID;
////////


kPID createkPID(kPID kPID, double kP, double kI, double kD){
  //struct kPID Kpid; <-- for optimization might wanna create a local variable to create kPID

  kPID.kP = kP;
  kPID.kI = kI;
  kPID.kD = kD;

  return kPID;
}


int PIDloop(kPID kPID, double units, double EncoderValue){
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
  voltage = (error*kPID.kI) + (integral*kPID.kI) + (derivative*kPID.kD);
  if(voltage > 127)
    voltage = 127;
  if(voltage < -127)
    voltage = -127;

  return voltage;
}

//pass in 2 structure "positions" with an X and Y
int PIDdrive(kPID kPID, double unitsX, double unitsY, double EncoderValue){
  int voltage;

  //sets error
  error = unitsX - EncoderValue;
  pros::lcd::print(0, "error: %f, %f, %f", error, unitsX, EncoderValue);
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
  voltage = (error*kPID.kI) + (integral*kPID.kI) + (derivative*kPID.kD);
  if(voltage > 127)
    voltage = 127;
  if(voltage < -127)
    voltage = -127;

  return voltage;
}

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
