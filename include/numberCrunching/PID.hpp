#include "main.h"

typedef struct kPID{
  double kP;
  double kI;
  double kD;
} kPID;

extern kPID forwardPID;
extern kPID turnPID;
    //HELPER FUNCTIONS

/*
Sets values for a kPID structure.

Paramaters:
Structure of type kPID to write to.
  This allows for setting a different kPID for different subsystems
Target kP, kI, kD for this structure.

*/

//PIDTuner stuff
extern okapi::PIDTunerFactory PIDTuner;
extern okapi::MotorGroup drive;

//helper functions
kPID createkPID(double kP, double kI, double kD);
kPID adjustkPID(kPID kPID, double kP, double kI, double kD);
//do stuff functions
kPID tunePID(kPID kPID);

int PIDdrive(kPID kPID, rectCoord targetPosition, position currPosition);

int PIDloop(kPID kPID, double units, double EncoderValue);

int PIDloop(float Kp, float Ki, float Kd, double units, double EncoderValue);
