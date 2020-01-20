#include "main.h"

bool autonRunning;
rectCoord target;
void setAutonButton(){
  while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) == 1)
  {
      forwardPID = createkPID(9, 0.0, 0.195);
      turnPID = createkPID(1.75, 0.0, 0.0);
      adjustPID = createkPID(0.75, 0.0, 0.05);
      setDriveCoast();
      while(1){
        updatePosition();
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
          break;
        if(driveStep == 1){
          translate(20.0, 0, 127);
        }
                  pros::delay(10);
      }
      //autonRunning = true;
      //autonStackFiveRed();//run auton
      //autonStackFiveBlue();
      //autonCorrect();
      //autonTest();
      //autonTurn();
      break;
  }

    autonRunning = false;
    setDriveBrake();
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

void autonCorrect(){
  translateY(0, 0.0, 117, 0.0, 0.65);
}

void autonStackFiveRed(){
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
    /*
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

        */
  }

}
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
