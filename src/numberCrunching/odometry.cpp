#include "main.h"




///////////////////////////////////////////////////////////////////////////
              //                                            //
              //Odometry variables-variables only used here //
              //                                            //
///////////////////////////////////////////////////////////////////////////

////current positions of tracking wheels
double positionL; //left wheel
double positionR; //right wheel
double positionH; //horizontal wheel

////initial tracking wheel values when resetting, normally should be 0
double initL = 0.0;
double initR = 0.0;
double initX = 0.0;

////position of tracking wheel positions in the loop before
double lastPositionL;
double lastPositionR;
double lastpositionH;

////change in position of the tracking wheels since the last cycle
double deltaL;
double deltaR;
double deltaX;

////total change in position of the tracking wheel since the last reset of tracking wheels
double deltaLr = 0.0;
double deltaRr = 0.0;

////angle stuff
double angle; //current calculated angle since last reset
double lastAngle; //angle at last reset
double deltaAngle; //change in angle since last cycle
double angleM; //angle of the adjusted XY coordinate plane for translations

////double
double initAngle = 0.0;



double dAngle;
/////////////////////////

void getPosition(){
//steps will correspond with Pilons thing

  //step 1 - update tracking wheels, convert to inches
  positionL = trackingLeft.get_value()*TR_TICK_INCH;
  positionR = trackingRight.get_value()*TR_TICK_INCH;
  positionH = trackingX.get_value()*TR_TICK_INCH;

  //step 2 - find change in tracking wheels since last cycle
  deltaL = positionL - lastPositionL;
  deltaR = positionR - lastPositionR;
  deltaX = positionH - lastpositionH;

  //step 3 - update lastPosition variables for the next cycle
  lastPositionL = positionL;
  lastPositionR = positionR;
  lastpositionH = positionH;

  //step 4 - find total change since the last reset
  deltaLr = positionL - initL;
  deltaRr = positionR - initR;

  //step 5 = find the change in angle using the cool equation
  angle = initAngle + (deltaLr-deltaRr)/(RIGHTWHEELDISTANCE+LEFTWHEELDISTANCE);

  //step 6 - find the change in angle since the last cycle
  deltaAngle = angle - lastAngle;


  lastAngle = angle;

  angle = angle*180.0/PI;
  printToBrain();
  ;
}
