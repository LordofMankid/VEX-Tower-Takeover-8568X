#include "main.h"

bool autonRunning;
bool runOnce = true;


//HELPER FUNCTIONS
void autonUpdate(){
  updatePosition();
  if(slopeLimit.get_value() == 1)
      slopeLift.tare_position();
  slopeAngle = slopeLift.get_position();

}

void delay(int time, int targDriveStep){
  if(driveStep == targDriveStep){
    pros::delay(500);
    driveStep++;
  }
}
/*
void startFunction(*function, int driveStepNumber, int subsysStep int subsystemStepNumber)
    if(subsysStep == subsystemStepNumber){
      if(driveStep == driveStepNumber){
        initial stuff;
      }
      runFunction();
    }

*/
void adjustkPID(kPID kPID, double kP, double kI, double kD, int driveStepNumber){

  if(driveStep == driveStepNumber){
    kPID = adjustkPID(kPID, kP, kI, kD);

  }
}

void setAutonButton(){
  while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) == 1)
  {
    forwardPID = createkPID(9.5, 0.0, 0.25);
    turnPID = createkPID(1.75, 0.0, 0.45);
    adjustPID = createkPID(2.0, 0.0, 0.045);
    driveStep = 0;
    setDriveCoast();
      //slopeTest();
      //intakeTest();
      //multipleSubsystemTest();
      //redStackFive();
      //blueStackFive();
      //autonCorrect();
      //scoreTurnLeft();
      autonDriveTest();
      break;
  }

    autonRunning = false;
    setDriveBrake();
}
void autonDriveTest(){
  while(1){
    autonUpdate();
    slopeMove(2500, 127, 0, 1);
    startIntake(1500, -127, 1, 1);
    delay(10, 1);
    delay(500, 2);
    slopeMove(0, -127, 3, 2);
    startIntake(5000, 127, 3, 2);
    translate(40.0, 0.0, 0.0, 50, 4);
    translate(-20.0, 0.0, 0.0, 100, 5);
    rotate(-135.0, 100, 6);
    if(driveStep == 7){
      if(runOnce == true){
          resetPosition();
          runOnce = false;
          driveStep++;
        }
    }

    translate(10.0, 0.0, 0.0, 30, 8);
    slopeMove(2500, 127, 9, 3);
    translate(-10.0, 0, 0, 30, 10);
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;



    /*
    delay(500, 7);
    translate(-10, 0.0, 0.0, 100, 8);
    delay(500, 9);
    rotate(-135, 100, 10);
    delay(500, 11);
    translate(10, 0.0, -135, 100, 12);
    printf("driveStep %i \n", driveStep);*/
    pros::delay(10);
  }

}
/*
void scoreTurnLeft(){
  while(1){
    autonUpdate();

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;
    //note for later, can you abuse the 'hold' boolean and have it start the intake, not letting any other intake commands go until you say stop
    slopeMove(2500, 127, 0, 1);
    startIntake(1500, -127, 1, 1);
    if(driveStep == 1){
      pros::delay(500);
      driveStep++;
    }
    slopeMove(0, 127, 2, 2);
    printf("slope %f", slopeAngle);
    if(driveStep == 3){
      translate(30.0, 0, 50);
      printf("hi there");
    }
    if(driveStep == 4){
      if(runOnce == true){
          resetPosition();
          runOnce = false;
          adjustkPID(forwardPID, 0.0, 0.0, 0.07);
          translate(-20.0, 0, 20);
    }
    if(driveStep == 5){
      translate(0, 0, 0);
    }

      printf(",hi there");
    }
    if(driveStep == 5){
      translate(0, 0, 0);
    }
    pros::delay(10);
  }

}

void scoreTurnRight(){
  while(1){
    autonUpdate();
    if(driveStep == 0)
      translate(20.0, 0, 100);
    if(driveStep == 1)
      translate(-20.0, 0, 100);
    if(driveStep == 2)
      rotate(90, 100);
    slopeMove(2500, 127, 3, 1);
    startIntake(1500, -127, 4, 1);
    if(driveStep == 4){
      pros::delay(500);
      driveStep++;
    }
    slopeMove(0, 127, 5, 2);
    pros::delay(10);
  }

}

void slopeTest(){

  while(1){
    autonUpdate();
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;
      slopeMove(2000, 127, 0, 1);
      if(driveStep == 1){
        pros::delay(1000);
        driveStep++;
      }
      slopeMove(0, 127, 2, 2);
      printf("driveStep %i\n", driveStep);
  }
}

void intakeTest(){
  while(1){
    autonUpdate();

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
    autonUpdate();
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;
    slopeMove(2500, 127, 0, 1);
    startIntake(1500, -127, 1, 1);
    if(driveStep == 1){
      pros::delay(500);
      driveStep++;
    }
    slopeMove(0, 127, 2, 2);
    startIntake(5000, 127, 3, 2);
    pros::delay(10);
  }

}

void redStackFive(){


    while(1){
      autonUpdate();
      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
        break;
      //note for later, can you abuse the 'hold' boolean and have it start the intake, not letting any other intake commands go until you say stop
      slopeMove(2500, 127, 0, 1);
      startIntake(1500, -127, 1, 1);
      if(driveStep == 1){
        pros::delay(500);
        driveStep++;
      }
      slopeMove(0, 127, 2, 2);
      printf("slope %f", slopeAngle);
      startIntake(5000, 127, 2, 2);
      if(driveStep == 3){
        translate(42.0, 0, 45);
        printf("hi there");
      }

      if(driveStep == 4){
        translate(0, 0, 0);
      }
      pros::delay(10);
    }
      printf("autonStep %i\n", driveStep);


}

void blueStackFive(){
  while(1){
    autonUpdate();

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;
    //note for later, can you abuse the 'hold' boolean and have it start the intake, not letting any other intake commands go until you say stop
    slopeMove(2500, 127, 0, 1);
    startIntake(1500, -127, 1, 1);
    if(driveStep == 1){
      pros::delay(500);
      driveStep++;
    }
    slopeMove(0, 127, 2, 2);
    printf("slope %f", slopeAngle);
    if(driveStep == 3){
      translate(45.0, 0, 45);
      printf("hi there");
    }
    startIntake(5000, 127, 3, 2);
    if(driveStep == 4){
      translate(-22.5, 0, 50);
    }
    if(driveStep == 5){
      rotate(-135, 100);
    }
    if(driveStep == 6){
      if(runOnce == true){
          resetPosition();
          runOnce = false;
      }
      translate(19.0, 0, 50);
    }
    slopeMove(5000, 127, 7, 3);
    if(driveStep == 8){
      translate(-19.0, 0, 50);
    }
    pros::delay(10);
  }
    printf("autonStep %i\n", driveStep);
}*/
/*
void autonCorrect(){
  while(1){
    autonUpdate();
    if(driveStep == 0)
      rotate(180.0, 100);
    pros::delay(10);
  }
}*/

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
*/
