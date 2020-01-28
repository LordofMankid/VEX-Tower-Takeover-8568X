#include "main.h"

float error;
float integral = 0;
float derivative;
float prevError = 0;
const int integralMax = 25;

kPID forwardPID;
kPID adjustPID;
kPID turnPID;
////////

//PIDTuner stuff
using namespace okapi;
//setup okapi stuff for PIDTuner
okapi::Motor myMotor(1);
okapi::MotorGroup drive({1,3,-2,-12});
okapi::ADIEncoder oTrackingX('A','B');
okapi::ADIEncoder oTrackingRight('G','H');

auto oTrackingLeft = okapi::ADIEncoder('C', 'D');
auto test = std::make_shared<okapi::ADIEncoder>(oTrackingRight);
//auto turn = std::make_shared<struct position>(position.angle);
auto testGroup = std::make_shared<okapi::MotorGroup>(drive);


okapi::PIDTuner drivePID = okapi::PIDTuner(test, testGroup, TimeUtilFactory::create(), 2500.0_ms, 40.0*TR_INCH_TICK, 0.000, 0.00016, 0.0000, 0.000, 0.000, 0.00);

//okapi::PIDTuner turnPID = okapi::PIDTuner(position.angle, testGroup, TimeUtilFactory::create(), 3000.0_ms, 20.0*TR_TICK_INCH, 0.001, 2.0, 0.0005, 0.1, 0.0001, 1.0);

  kPID createkPID(double kP, double kI, double kD){
    kPID kPID;
    kPID.kP = kP;
    kPID.kI = kI;
    kPID.kD = kD;

    return kPID;
  }

  kPID adjustkPID(kPID kPID, double kP, double kI, double kD){
    kPID.kP += kP;
    kPID.kI += kI;
    kPID.kD += kD;

    return kPID;
  }

kPID tunePID(kPID kPID){
  okapi::PIDTuner::Output bestPID;

  bestPID = drivePID.autotune();

  kPID.kP = bestPID.kP;
  kPID.kI = bestPID.kI;
  kPID.kD = bestPID.kD;
  //okapi::QTime

  return kPID;
}


int PIDloop(kPID kPID, double units, double EncoderValue){
  int voltage;

  //sets error
  error = units - EncoderValue;
  pros::lcd::print(0, "error: %f, %f, %f", error, units, EncoderValue);
  printf("encoder value %f\n units %f\n error %f\n", EncoderValue, units, error);
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
  voltage = (error*kPID.kP) + (integral*kPID.kI) + (derivative*kPID.kD);
  if(voltage > 127)
    voltage = 127;
  if(voltage < -127)
    voltage = -127;

  return voltage;
}

//pass in 2 structure "positions" with an X and Y
int PIDdrive(kPID kPID, double targetDistance, double distanceFromTarget){
    int voltage;

    //sets error
    error = autonDirection*distanceFromTarget;
    
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
    voltage = (error*kPID.kP) + (integral*kPID.kI) + (derivative*kPID.kD);
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
