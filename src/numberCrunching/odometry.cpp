#include "main.h"

//GLOBALS

struct position position;
polarCoord polarCoords;
rectCoord rectCoords;

///////////////////////////////////////////////////////////////////////////
              //                                            //
              //Odometry variables-variables only used here //
              //                                            //
///////////////////////////////////////////////////////////////////////////

////current positions of tracking wheels
double positionL; //left wheel
double positionR; //right wheel
double positionH; //horizontal wheel

////change of position, in coordinates
double deltaPositionX; //change of position along X axis
double deltaPositionY; //change of position along Y axis

////initial tracking wheel values when resetting, normally should be 0
double initL = 0.0;
double initR = 0.0;
double initX = 0.0;

////position of tracking wheel positions in the loop before
double lastPositionL;
double lastPositionR;
double lastpositionH;

////change in position of the tracking wheels since the last cycle
double deltaL; //change in position of the left tracking wheel since the last cycle
double deltaR; //change in position of the right tracking wheel since the last cycle
double deltaX; //change in position of the horizontal tracking wheel since the last cycle

////total change in position of the tracking wheel since the last reset of tracking wheels
double deltaLr = 0.0;
double deltaRr = 0.0;

////angle stuff
double angle; //current calculated angle since last reset
double lastAngle; //angle at last reset
double deltaAngle; //change in angle since last cycle
double angleM; //angle of the adjusted XY coordinate plane for translations

////polar coordinate stuff
double theta = 0;
double radius = 0;

double deltaXtest;
////double
double initAngle = 0.0;



double dAngle;
/////////////////////////


/////HELPER FUNCTIONS///

polarCoord rectToPolar(double x, double y){
    polarCoord polarCoord;
    polarCoord.radius = sqrt(x*x+y*y);
    polarCoord.angle = atan2(y, x);

    return polarCoord;
}

rectCoord polarToRect(double r, double theta){
    rectCoord rectCoord;
    rectCoord.x = r*cos(theta);
    rectCoord.y = r*sin(theta);

    return rectCoord;
}

/////THE JUICE/////


void updatePosition(){
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
  deltaXtest = deltaX - XWHEELDISTANCE*deltaAngle; //accounts for the tracking wheel's turning distance using the arclength formulra

  //step 7 - Record the XY coordinate changes of the robot - if change in angle = 0, then it's just the straight up XY distance
  if(deltaAngle == 0){ //also makes it so you don't divide by 0 lol
    deltaPositionX = deltaX;
    deltaPositionY = deltaR;
  }
  //step 8 - Record the XY coordinate changes of the robot accounting for a change in orientation, then it "turns" the XY coordinates
  else{
    deltaPositionX = (2*sin(deltaAngle/2))*(deltaX/deltaAngle + XWHEELDISTANCE);
    deltaPositionY = (2*sin(deltaAngle/2))*(deltaR/deltaAngle + RIGHTWHEELDISTANCE);
  }

  //step 9 - Calculate
  angleM = angle + deltaAngle/2;;



  //step 10 - Adjust XY coordinates to regular coordinate by changing to polar coordinates, adding angleM, and changing back
    //Converts to polar coodinates
  theta = atan2f(deltaPositionY, deltaPositionX); //finds the angle
  radius = sqrt(deltaPositionX*deltaPositionX + deltaPositionY*deltaPositionY); //finds the radius
    //Changes the angle to the regular coordinate system (this adjusts the X/Y coordinate tilting thing)
  theta = theta - angleM;
    //Converts back from polar coordinates

  deltaPositionX = radius*cos(theta);
  deltaPositionY = radius*sin(theta);

    //Converts angle to between 0 and 2pi (it's in radians right now)
  /*angle += PI;
  while(angle < 0) {
    angle +=2*PI;
  }
  angle = modulo(angle, 2*PI);
  angle -= PI;*/

  //step 11 - Update final positions
  lastAngle = angle;

//  angle = angle*180.0/PI; //converts to degrees
  if(fabs(deltaPositionX) > 10)
    deltaPositionX = 0;
  if(fabs(deltaPositionY) > 10)
    deltaPositionY = 0;

  position.xPosition = position.xPosition + deltaPositionX;
  position.yPosition = position.yPosition + deltaPositionY;
  position.angle = angle; //orientation in radians
  printf("deltaXtest %f\ndeltaAngle %f\ndeltaX %f\n", deltaXtest, XWHEELDISTANCE*deltaAngle, deltaX);
//  pros::lcd::print(4, "X: %f", position.xPosition);
//  pros::lcd::print(5, "R: %f", position.yPosition);
//  pros::lcd::print(6, "A: %f", position.angle*180/PI);



}

double modulo(double a, double b) {
  while (a>b) {
    a-=b;
  }
  return a;
}

double getXposition(){
  return position.xPosition;
}

double getYposition(){
  return position.yPosition;
}

double getAngleRad(){
  return position.angle;
}

double getAngleDeg(){
  return position.angle*180/PI;
}
