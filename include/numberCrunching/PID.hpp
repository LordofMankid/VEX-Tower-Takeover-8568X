#include "main.h"

typedef struct kPID{
  double kP;
  double kI;
  double kD;
} kPID;

    //HELPER FUNCTIONS

/*
Sets values for a kPID structure.

Paramaters:
Structure of type kPID to write to.
  This allows for setting a different kPID for different subsystems
Target kP, kI, kD for this structure.

*/
kPID createkPID(kPID kPID, double kP, double kI, double kD);

int PIDloop(kPID kPID, double units, double EncoderValue);

int PIDloop(float Kp, float Ki, float Kd, double units, double EncoderValue);
