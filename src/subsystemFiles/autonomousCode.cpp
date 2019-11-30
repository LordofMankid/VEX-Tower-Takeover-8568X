#include "main.h"

bool autonRunning;

void setAutonButton(){
  while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) == 1)
  {
      autonRunning = true;
      autonStackFiveRed();//run auton
      //autonStackFiveBlue();
      //autonCorrect();
      //autonTest();
      //autonTurn();
      break;
  }

    autonRunning = false;
    setDriveBrake();
}

//////kuashdfkjhasd
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
