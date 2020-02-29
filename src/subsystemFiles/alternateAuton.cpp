#include "main.h"

using namespace okapi;
auto leftSide = okapi::MotorGroup({1,3});
auto rightSide = okapi::MotorGroup({-2,-12});

auto myChassis = ChassisControllerFactory::create(
  leftSide,
  rightSide,
  AbstractMotor::gearset::green, // Torque gearset
  {4_in, 12.5_in} // 4 inch wheels, 12.5 inch wheelbase width
);

auto profileController = AsyncControllerFactory::motionProfile(
  1.0,  // Maximum linear velocity of the Chassis in m/s
  2.0,  // Maximum linear acceleration of the Chassis in m/s/s
  10.0, // Maximum linear jerk of the Chassis in m/s/s/s
  myChassis // Chassis Controller
);

void opcontrol() {
  profileController.generatePath({Point{0_ft, 0_ft, 0_deg}, Point{3_ft, 0_ft, 0_deg}}, "A");
  profileController.setTarget("A");

  profileController.waitUntilSettled();
}

void timeDrive(int time, int voltage){
  int direction = abs(voltage)/voltage;
  pros::c::imu_accel_s_t accel = inertia_sensor.get_accel();
  time += pros::millis();
  resetDriveEncoders();
  inertia_sensor.reset();

  while(pros::millis() > time){
    setDrive(voltage, 0);
    printf("%f,%f,%f\n", accel.x, accel.y, accel.z);
    pros::delay(10);
  }
  setDrive(0, 0);
}
