#include "main.h"

using namespace okapi;
auto leftSide = okapi::MotorGroup({1,3});
auto rightSide = okapi::MotorGroup({2,12});
const QLength WHEELDIAMETER = 3.25_in;


MotorGroup intake({-19, 10});
Motor slopeMotor(7);
/*
pros::Motor slopeLift(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FrontLeft(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BackLeft(3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FrontRight(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BackRight(12, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeLeft(19, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeRight(10, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor armLift(11, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Imu inertial_sensor(16);
*/


std::shared_ptr<ChassisController> myChassis =
  ChassisControllerBuilder()
    .withMotors(leftSide, rightSide)
    // Green gearset, 4 in wheel diam, 11.5 in wheel track
    .withDimensions(AbstractMotor::gearset::green, {{WHEELDIAMETER, 8.75_in}, imev5GreenTPR})
    .build();

std::shared_ptr<AsyncMotionProfileController> profileControllerF =
  AsyncMotionProfileControllerBuilder()
    .withLimits({1.5, 2.0, 10.0})
    .withOutput(myChassis)
    .buildMotionProfileController();

std::shared_ptr<AsyncMotionProfileController> profileControllerM =
  AsyncMotionProfileControllerBuilder()
    .withLimits({0.5, 2.0, 10.0})
    .withOutput(myChassis)
    .buildMotionProfileController();

std::shared_ptr<AsyncMotionProfileController> profileControllerS =
  AsyncMotionProfileControllerBuilder()
    .withLimits({0.25, 2.0, 10.0})
    .withOutput(myChassis)
    .buildMotionProfileController();

auto slopeController = AsyncPosControllerBuilder()
  .withMotor(slopeMotor)
  .withGearset(AbstractMotor::gearset::green)
  .withSensor(slopeMotor)
  .build();

auto intakeController = AsyncVelControllerBuilder()
  .withMotor(intake)
  .withMaxVelocity(600)
  .withGearset(AbstractMotor::gearset::red)
  .build();

auto intakeControllerOut = AsyncVelControllerBuilder()
  .withMotor(intake)
  .withMaxVelocity(600)
  .withGearset(AbstractMotor::gearset::red)
  .build();

void eightStack(){
  profileControllerF->generatePath(
    {{0_ft, 0_ft, 0_deg}, {30_in, 0_ft, 0_deg}}, "Movement 1", {1.0, 0.9, 5.0});

  profileControllerF->generatePath(
    {{0_ft, 0_ft, 0_deg}, {-5_in, 0_in, 0_deg}, {-30_in, -27.5_in, 0_deg}}, "Movement 2", {1.5, 0.9, 7.5});

  profileControllerF->generatePath(
    {{0_ft, 0_ft, 0_deg}, {35_in, 0_ft, 0_deg}}, "Movement 3", {1.5, 0.9, 7.5});

  profileControllerF->generatePath(
    {{0_ft, 0_ft, 0_deg}, {18_in, 5_in, 0_deg}}, "Movement 4", {1.5, 0.9, 7.5});

    profileControllerF->setTarget("Movement 1");
    profileControllerF->waitUntilSettled(); //blocks everything else until finished


    profileControllerF->setTarget("Movement 2", true); //"True" reverses it
    profileControllerF->waitUntilSettled();

    profileControllerF->setTarget("Movement 3"); //"True" reverses it
    profileControllerF->waitUntilSettled();

}

void autonTest() {
  ////Path Generation
  /*
  Goes as follows:
  generatePath({inside these brackets is the targets}, "Movement name", {velocityLimit, accelerationLimit, "jerk" limit})
  The 3rd one is optional
  */


  slopeController->setMaxVelocity(600);
  slopeController->setTarget(4000);
  intakeController->setTarget(-600);
  slopeController->waitUntilSettled();
  slopeController->setTarget(0);
  intakeController->setTarget(600);
/*
  profileControllerF->generatePath(
    {{0_ft, 0_ft, 0_deg}, {10_in, 0_ft, 0_deg}, {39_in, -15_in, 0_deg}}, "Movement 1", {1.0, 0.9, 5.0});

  profileControllerF->generatePath(
    {{0_ft, 0_ft, 0_deg}, {16_in, 0_ft, 0_deg}}, "Movement 2", {1.5, 0.9, 7.5});

  profileControllerF->generatePath(
    {{0_ft, 0_ft, 0_deg}, {25_in, 0_ft, 0_deg}}, "Movement 3", {1.5, 0.9, 7.5});

  profileControllerF->generatePath(
    {{0_ft, 0_ft, 0_deg}, {18_in, 5_in, 0_deg}}, "Movement 4", {1.5, 0.9, 7.5});

  profileControllerF->setTarget("Movement 1");
  intakeController->setTarget(1000);
  profileControllerF->waitUntilSettled(); //blocks everything else until finished
  gyroTurn(-90.0, 40);

  profileControllerF->setTarget("Movement 2"); //"True" reverses it
  profileControllerF->waitUntilSettled();

  gyroTurn(-90.0, 42);


  profileControllerF->setTarget("Movement 3"); //"True" reverses it
  profileControllerF->waitUntilSettled();

  gyroTurn(-90, 42);

  profileControllerF->setTarget("Movement 4"); //"True" reverses it
  profileControllerF->waitUntilSettled();
*/
}

void timeDrive(int time, int voltage){
  int direction = abs(voltage)/voltage;

  //resetDriveEncoders();
  inertia_sensor.reset();
  while(inertia_sensor.reset()){
    pros::delay(10);
  }
  time += pros::millis();
  while(pros::millis() < time){
    pros::c::imu_accel_s_t accel = inertia_sensor.get_accel();

    setDrive(voltage, 0);
    printf("%f,%f,%f\n", accel.x, accel.y, accel.z);
    pros::delay(10);
  }
  setDrive(0, 0);
}
