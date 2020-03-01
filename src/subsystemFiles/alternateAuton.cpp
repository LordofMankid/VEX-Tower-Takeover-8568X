#include "main.h"

using namespace okapi;
auto leftSide = okapi::MotorGroup({1,3});
auto rightSide = okapi::MotorGroup({-2,-12});
const QLength WHEELDIAMETER = 4_in;


MotorGroup intake({-14, 10});
Motor slopeMotor(7);
/*
pros::Motor slopeLift(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FrontLeft(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BackLeft(3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor FrontRight(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor BackRight(12, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeLeft(14, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeRight(10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor armLift(8, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Imu inertia_sensor(16);
*/


std::shared_ptr<ChassisController> myChassis =
  ChassisControllerBuilder()
    .withMotors(leftSide, rightSide)
    // Green gearset, 4 in wheel diam, 11.5 in wheel track
    .withDimensions(AbstractMotor::gearset::green, {{WHEELDIAMETER, 11.5_in}, imev5GreenTPR})
    .build();

std::shared_ptr<AsyncMotionProfileController> profileControllerF =
  AsyncMotionProfileControllerBuilder()
    .withLimits({1.0, 2.0, 10.0})
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

auto slopeController = AsyncVelControllerBuilder()
  .withMotor(slopeMotor)
  .withGearset(AbstractMotor::gearset::green)
  .build();

auto intakeControllerIn = AsyncVelControllerBuilder()
  .withMotor(intake)
  .withMaxVelocity(200)
  .withGearset(AbstractMotor::gearset::red)
  .build();

auto intakeControllerOut = AsyncVelControllerBuilder()
  .withMotor(intake)
  .withMaxVelocity(-110.23622072)
  .withGearset(AbstractMotor::gearset::red)
  .build();

void autonTest() {

  profileControllerF->generatePath(
    {{0_ft, 0_ft, 0_deg}, {3_ft, 0_ft, 0_deg}}, "Movement 1");
  profileControllerF->setTarget("Movement 1");
  intakeControllerIn->setTarget(200);

  profileControllerF->waitUntilSettled();


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
