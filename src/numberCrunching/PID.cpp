#include "main.h"

float error;
float integral = 0;
float derivative;
float prevError = 0;
const int integralMax = 25;

////////

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
