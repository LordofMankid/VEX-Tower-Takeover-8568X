  #include "main.h"

bool autonRunning;
bool runOnce = true;
int delayStep = 0;


//HELPER FUNCTIONS
void autonUpdate(){
  updatePosition();
  if(slopeLimit.get_value() == 1)
      slopeLift.tare_position();

  slopeAngle = slopeLift.get_position();
  armAngle = armLift.get_position();
}

void delay(int time, int targDriveStep){
  if(driveStep == targDriveStep){
    pros::delay(500);
    driveStep++;
  }
}

void coolDelay(int time, int targDriveStep){
  if(driveStep == targDriveStep){
      delayStep++;
  }
  if(delayStep == time/10){
    driveStep++;
    delayStep = 0;
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
    forwardPID = createkPID(12.5, 0.0, 2.0);
    turnPID = createkPID(1.75, 0.0, 0.45);
    adjustPID = createkPID(2.0, 0.0, 0.045);
    armPID = createkPID(0.0, 0.0, 0.0);
    driveStep = 0;
    setDriveCoast();
    while(1){
      autonUpdate();
      if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
        break;
      driveTest();
      pros::delay(10);
    }

    //armTest();
      //slopeTest();
      //intakeTest();
      //multipleSubsystemTest();
      //redFiveStack();
      //blueStackFive();
      //autonCorrect();
      //scoreTurnLeft();
      //blueFiveStack();
      //autonSkills();
      //protectedBlue();
      break;
  }

    autonRunning = false;
    setDriveBrake();
}

void slopeTest(){
  while(1){
    autonUpdate();
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;

    slopeMove(1500, 127, 0, 1);
    coolDelay(500, 1);
    slopeMove(0, 127, 2, 2);
    pros::delay(10);
  }

}
void armTest(){
  while(1){
    autonUpdate();
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;

    armMove(1500, 127, 0, 1);
    coolDelay(500, 1);
    armMove(0, 127, 2, 2);
    pros::delay(10);
  }

}

void driveTest(){

  translate(40.0, 0.0, 0.0, 100, 0);
  translate(-20.0, 0.0, 0.0, 100, 1);
  rotate(45, 70, 2);
  translate(20.0, 0.0, 45.0, 100, 3);
  pros::delay(10);
}

void autonSkills(){

  while(1){
    autonUpdate();
    slopeMove(3000, 127, 0, 1);
    startIntake(1500, -127, 1, 1);
    delay(10, 1);
    delay(500, 2);
    startSlopeMove(0, -127, 3, 2);
    startIntake(15000, 127, 3, 2);
    translate(10.0, 0.0, 0.0, 30, 3);
    translate(106.0, 0.0, 0.0, 45, 4);
    translate(10.0, 0.0, 0.0, 100, 5);
    translate(-15.0, 0.0, 0.0, 60, 6);
  //  startIntake(200, -80, 5, 3);
    rotate(45.0, 70, 7);
    if(driveStep == 8){
      if(runOnce == true){
          resetPosition();
          runOnce = false;
          driveStep++;
        }
    }

    //startSlopeMove(1500, 127, 8, 3);
    translate(16.0, 0.0, 0.0, 60, 9);
    slopeMove(5000, 127, 10, 4);
    translate(-12.0, 0, 0, 35, 11);


    pros::delay(10);
  }

}
void redFiveStack(){
  autonRunning = false;
  FrontLeft.move_absolute(8.0*REG_INCH_TICK, 75);
  FrontRight.move_absolute(8.0*REG_INCH_TICK, 75);
  BackLeft.move_absolute(8.0*REG_INCH_TICK, 75);
  BackRight.move_absolute(8.0*REG_INCH_TICK, 75);
  while(!((FrontLeft.get_position() < 4.1*REG_INCH_TICK) && (FrontLeft.get_position() > 3.9*REG_INCH_TICK))){

    pros::delay(10);
  }
  pros::delay(200);
  FrontLeft.move_absolute(0, 65);
  FrontRight.move_absolute(0, 65);
  BackLeft.move_absolute(0, 65);
  BackRight.move_absolute(0, 65);
  while(!((FrontLeft.get_position() < 5) && (FrontLeft.get_position() > -5))){
    delayStep++;
    pros::delay(10);
    if(delayStep > 50)
      break;
  }

  resetPosition();
 autonRunning = true;

  while(autonRunning == true){
    autonUpdate();
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;

    slopeMove(3500, 127, 0, 1);
    startIntake(1500, -127, 1, 1);
    delay(100, 1);
    startSlopeMove(0, -127, 2, 2);
    coolDelay(600, 2);
    startSlopeMove(0, -127, 3, 3);
    startIntake(5000, 127, 3, 2);
    translate(10.0, 0.0, 0.0, 30, 3);
    translate(34.0, 0.0, 0.0, 51, 4);
    translate(-20.0, 0.0, 0.0, 100, 5);
    startIntake(300, -110, 6, 3);
    rotate(135.0, 70, 6);
    if(driveStep == 7){
      if(runOnce == true){
          resetPosition();
          runOnce = false;
          driveStep++;
        }
    }

    startSlopeMove(1500, 127, 8, 4);
    translate(16.5, 0.0, 0.0, 70, 8);
    slopeMove(5000, 127, 9, 5);
    translate(-12.0, 0, 0, 50, 10);


    pros::delay(10);
  }
}


void blueFiveStack(){
  autonRunning = false;
  FrontLeft.move_absolute(8.0*REG_INCH_TICK, 75);
  FrontRight.move_absolute(8.0*REG_INCH_TICK, 75);
  BackLeft.move_absolute(8.0*REG_INCH_TICK, 75);
  BackRight.move_absolute(8.0*REG_INCH_TICK, 75);
  while(!((FrontLeft.get_position() < 4.1*REG_INCH_TICK) && (FrontLeft.get_position() > 3.9*REG_INCH_TICK))){

    pros::delay(10);
  }
  pros::delay(200);
  FrontLeft.move_absolute(0, 65);
  FrontRight.move_absolute(0, 65);
  BackLeft.move_absolute(0, 65);
  BackRight.move_absolute(0, 65);
  while(!((FrontLeft.get_position() < 5) && (FrontLeft.get_position() > -5))){
    delayStep++;
    pros::delay(10);
    if(delayStep > 50)
      break;
  }

  resetPosition();
 autonRunning = true;

  while(autonRunning == true){
    autonUpdate();
    slopeMove(3500, 127, 0, 1);
    startIntake(1500, -127, 1, 1);
    delay(100, 1);
    startSlopeMove(0, -127, 2, 2);
    coolDelay(600, 2);
    startSlopeMove(0, -127, 3, 3);
    startIntake(5000, 127, 3, 2);
    translate(10.0, 0.0, 0.0, 30, 3);
    translate(34.0, 0.0, 0.0, 51, 4);
    translate(-20.0, 0.0, 0.0, 100, 5);
    startIntake(300, -110, 6, 3);
    rotate(-135.0, 70, 6);
    if(driveStep == 7){
      if(runOnce == true){
          resetPosition();
          runOnce = false;
          driveStep++;
        }
    }

    startSlopeMove(1500, 127, 8, 4);
    translate(16.5, 0.0, 0.0, 70, 8);
    slopeMove(5000, 127, 9, 5);
    translate(-12.0, 0, 0, 50, 10);
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;


    pros::delay(10);
  }
}

void protectedBlue(){
  autonRunning = false;
  FrontLeft.move_absolute(6.0*REG_INCH_TICK, 75);
  FrontRight.move_absolute(6.0*REG_INCH_TICK, 75);
  BackLeft.move_absolute(6.0*REG_INCH_TICK, 75);
  BackRight.move_absolute(6.0*REG_INCH_TICK, 75);
  while(!((FrontLeft.get_position() < 4.1*REG_INCH_TICK) && (FrontLeft.get_position() > 3.9*REG_INCH_TICK))){

    pros::delay(10);
  }
  pros::delay(200);
  FrontLeft.move_absolute(0, 65);
  FrontRight.move_absolute(0, 65);
  BackLeft.move_absolute(0, 65);
  BackRight.move_absolute(0, 65);
  while(!((FrontLeft.get_position() < 5) && (FrontLeft.get_position() > -5))){

    pros::delay(10);
  }

  resetPosition();
 autonRunning = true;

  while(autonRunning == true){
    autonUpdate();
    slopeMove(3500, 127, 0, 1);
    startIntake(1500, -127, 1, 1);
    delay(100, 1);
    startSlopeMove(0, -127, 2, 2);
    coolDelay(600, 2);
    startSlopeMove(0, -127, 3, 3);
    startIntake(4000, 127, 3, 2);
    translate(10.0, 0.0, 0.0, 30, 3);
    translate(30.5, 0.0, 0.0, 51, 4);

    rotate(120.5, 70, 5);
    if(driveStep == 6){
      if(runOnce == true){
          resetPosition();
          runOnce = false;
          driveStep++;
        }
    }
    startIntake(2100, 110, 7, 3);
    translate(38.0, 0.0, 0.0, 60, 7);
    startIntake(300, -110, 8, 4);
    slopeMove(5000, 127, 8, 5);
    translate(-12.0, 0, 0, 50, 9);
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
      break;


    pros::delay(10);
  }

}

void protectedRed(){
  autonRunning = false;
  FrontLeft.move_absolute(6.0*REG_INCH_TICK, 75);
  FrontRight.move_absolute(6.0*REG_INCH_TICK, 75);
  BackLeft.move_absolute(6.0*REG_INCH_TICK, 75);
  BackRight.move_absolute(6.0*REG_INCH_TICK, 75);
  while(!((FrontLeft.get_position() < 4.1*REG_INCH_TICK) && (FrontLeft.get_position() > 3.9*REG_INCH_TICK))){

    pros::delay(10);
  }
  pros::delay(200);
  FrontLeft.move_absolute(0, 65);
  FrontRight.move_absolute(0, 65);
  BackLeft.move_absolute(0, 65);
  BackRight.move_absolute(0, 65);
  while(!((FrontLeft.get_position() < 5) && (FrontLeft.get_position() > -5))){

    pros::delay(10);
  }

  resetPosition();
 autonRunning = true;

   while(autonRunning == true){
     autonUpdate();
     slopeMove(3500, 127, 0, 1);
     startIntake(1500, -127, 1, 1);
     delay(100, 1);
     startSlopeMove(0, -127, 2, 2);
     coolDelay(600, 2);
     startSlopeMove(0, -127, 3, 3);
     startIntake(4000, 127, 3, 2);
     translate(10.0, 0.0, 0.0, 30, 3);
     translate(30.5, 0.0, 0.0, 51, 4);

     rotate(-120.5, 70, 5);
     if(driveStep == 6){
       if(runOnce == true){
           resetPosition();
           runOnce = false;
           driveStep++;
         }
     }
     startIntake(2100, 110, 7, 3);
     translate(38.0, 0.0, 0.0, 60, 7);
     startIntake(300, -110, 8, 4);
     slopeMove(5000, 127, 8, 5);
     translate(-12.0, 0, 0, 50, 9);
     if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1)
       break;


     pros::delay(10);
   }

}

void scoreTurnLeft(){
  autonRunning = false;
  FrontLeft.move_absolute(7.5*REG_INCH_TICK, 75);
  FrontRight.move_absolute(7.5*REG_INCH_TICK, 75);
  BackLeft.move_absolute(7.5*REG_INCH_TICK, 75);
  BackRight.move_absolute(7.5*REG_INCH_TICK, 75);
  while(!((FrontLeft.get_position() < 4.1*REG_INCH_TICK) && (FrontLeft.get_position() > 3.9*REG_INCH_TICK))){

    pros::delay(10);
  }
  pros::delay(200);
  FrontLeft.move_absolute(0, 65);
  FrontRight.move_absolute(0, 65);
  BackLeft.move_absolute(0, 65);
  BackRight.move_absolute(0, 65);
  while(!((FrontLeft.get_position() < 5) && (FrontLeft.get_position() > -5))){

    pros::delay(10);
  }

}
