#include "main.h"

bool autonRunning;
rectCoord target;
void setAutonButton(){
  while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) == 1)
  {
    forwardPID = createkPID(9.5, 0.0, 0.25);
    turnPID = createkPID(1.75, 0.0, 0.0);
    adjustPID = createkPID(2.0, 0.0, 0.045);
    driveStep = 0;
    setDriveCoast();
      //slopeTest();
      //intakeTest();
      //multipleSubsystemTest();
      //redStackFive();
      //blueStackFive();
      //autonTurn();
      break;
  }

    autonRunning = false;
    setDriveBrake();
}

void slopeTest(){

  while(1){
    updatePosition();
    if(slopeLimit.get_value() == 1)
        slopeLift.tare_position();
    slopeAngle = slopeLift.get_position();
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;
      slopeMove(2000, 127, 0, 1);
      if(driveStep == 1){
        pros::delay(1000);
        driveStep++;
      }
      slopeMove(2000, 127, 2, 2);
      printf("driveStep %i", driveStep);
  }
}

void intakeTest(){
  while(1){
    updatePosition();
    if(slopeLimit.get_value() == 1)
        slopeLift.tare_position();
    slopeAngle = slopeLift.get_position();
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;
    startIntake(1000, 127, 0, 1);
    if(driveStep == 0){
      pros::delay(2000);
      driveStep++;
    }
    startIntake(1000, -127, 1, 2);

  }

}

void multipleSubsystemTest(){
  while(1){
    updatePosition();
    if(slopeLimit.get_value() == 1)
        slopeLift.tare_position();
    slopeAngle = slopeLift.get_position();
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;
    startIntake(1000, 127, 0, 1);
    slopeMove(3600, 127, 0, 1);
    startIntake(1000, -127, 1, 2);
    slopeMove(0, 127, 1, 2);
  }

}

void redStackFive(){

  while(1){
    updatePosition();
    if(slopeLimit.get_value() == 1)
        slopeLift.tare_position();
    slopeAngle = slopeLift.get_position();
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;
    //note for later, can you abuse the 'hold' boolean and have it start the intake, not letting any other intake commands go until you say stop
    startIntake(2000, -127, 0, 1);
    startSlopeMove(3600, 127, 0, 1);
    nextStep(1, 0);
    if(driveStep == 1){
      translate(45.0, 0, 50);
      printf("hi there");
    }
    startIntake(5000, 127, 1, 2);
    startSlopeMove(0, 127, 1, 2);
    if(driveStep == 2)
      translate(-35, 0, 50);
    if(driveStep == 3)
      rotate(135, 100);
    if(driveStep == 4)
      translate(10, 0, 50);
    slopeMove(5000, 127, 5, 3);
    if(driveStep == 6)
      translate(-10, 0, 30);
    pros::delay(10);
  }
}

void blueStackFive(){
  forwardPID = createkPID(9.5, 0.0, 0.25);
  turnPID = createkPID(1.75, 0.0, 0.0);
  adjustPID = createkPID(2.0, 0.0, 0.045);
  setDriveCoast();
  while(1){
    updatePosition();
    if(slopeLimit.get_value() == 1)
        slopeLift.tare_position();
    slopeAngle = slopeLift.get_position();
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;
    //note for later, can you abuse the 'hold' boolean and have it start the intake, not letting any other intake commands go until you say stop
    startIntake(2000, -127, 0, 1);
    startSlopeMove(3600, 127, 0, 1);
    nextStep(1, 0);
    if(driveStep == 1){
      translate(45.0, 0, 50);
      printf("hi there");
    }
    startIntake(5000, 127, 1, 2);
    startSlopeMove(0, 127, 1, 2);
    if(driveStep == 2)
      translate(-35, 0, 50);
    if(driveStep == 3)
      rotate(135, 100);
    if(driveStep == 4)
      translate(10, 0, 50);
    slopeMove(5000, 127, 5, 3);
    if(driveStep == 6)
      translate(-10, 0, 30);
    pros::delay(10);
  }
}
void autonCorrect(){
  translateY(0, 0.0, 117, 0.0, 0.65);
}

/*void autonStackFiveRed(){
  double firstMove;
  //Flips out slope
  intakeOut();
  pros::delay(1000);
  intakeStop();
  pros::delay(1000);
  //Move forward
  intakeIn();
  translateY(30, 0.0, 40, -0.00, 0.65);

  //Start picking up cubes, move forward more slowly
  //stops intake when cubes are being held in
  intakeStop();
  //move back to original position
  pros::lcd::print(1, "tturning");
  rotatePID(135.0, 64, 0.0045);
  pros::lcd::print(1, "moving");
  translateY(25.75, 7.75, 102, 0.03, 0.65);
  //pros::delay(325);
  //intakeOut();
  pros::lcd::print(1, "stacking");
  slopeUp(5550, 87);
  setSlopeLift(0);
  intakeStop();
  //move back
  translateY(-10.0, 0.0, 35, 0.0, 0.65);
}

//
void autonTurn(){
  rotatePID(90.0, 100,0.0);
}

void autonTest(){
//  translateX(24.0, 127);
//  slopeUp(5500);
armTo(24.0, 127);
}

void autonStackFiveBlue(){

  //Flips out slope
  intakeOut();
  pros::delay(1000);
  intakeStop();
  pros::delay(1000);
  //Move forward
  intakeIn();
  translateY(30, 0.0, 40, -0.00, 0.65);

  //Start picking up cubes, move forward more slowly
  //stops intake when cubes are being held in
  intakeStop();
  //move back to original position
  pros::lcd::print(1, "tturning");
  rotatePID(-135.0, 64, 0.0045);
  pros::lcd::print(1, "moving");
  translateY(25.75, -8.75, 102, 0.03, 0.65);
  //pros::delay(325);
  //intakeOut();
  pros::lcd::print(1, "stacking");
  slopeUp(5550, 82);
  setSlopeLift(0);
  intakeStop();
  //move back
  translateY(-10.0, 0.0, 35, 0.0, 0.65);
  }

void scoreOneRight(){
  intakeOut();
  pros::delay(1000);
  intakeStop();
  pros::delay(1000);
  translateX(24.0, 127);
  translateX(-24.0, 127);
}

void scoreOneLeft(){
  pros::delay(1000);
  intakeOut();
  intakeStop();
  pros::delay(1000);
  translateX(-24.0, 127);
  translateX(24.0, 127);
}

void autonloopTest(){
  while(1){

    static int translateStep;

    updatePosition(); <-- modifies a positionInfo structure
    if(translateStep = 1){
    translate(*positionInfo, positionX, position Y); //static bool positionReached? also pass in a reference to a structure would b epic
    translateStep + positionReached;
  }
    else if(translateStep = 2){
    intakeIn(time); <-- note have a way to only start this once (don't want to start on loop) if on time control maybe subtract from a target time that we input
    translate(positionX, position Y);
    translateStep + positionReached;
  }


}

}*/
void autonSkills(){

    double firstMove;
    //Flips out slope

    intakeOut();

    pros::delay(1000);

    intakeStop();

    pros::delay(1000);

    //Move forward
    intakeIn();

    translateY(80, 0, 40, -0.00, 0.65);

    intakeStop();

    rotatePID(40, 67, 0.00);

}
