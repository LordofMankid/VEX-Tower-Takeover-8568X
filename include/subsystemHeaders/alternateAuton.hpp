#include "main.h"

//CONSTANTS
extern const double REG_INCH_TICK;

//HELPER FUNCTIONS
/*
Resets the drive's recorded encoder values to 0.
*/
void resetDriveEncoders();

/*
Finds the average distance traveled (in encoder ticks) of all the drive encoders.
*/
double avgDriveEncoderValue();

//DRIVE FUNCTIONS
void translateY_reg(double distance, int voltage);
