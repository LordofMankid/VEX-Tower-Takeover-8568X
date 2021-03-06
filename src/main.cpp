#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	printf("initialize");
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	setUp();
	pros::lcd::register_btn1_cb(on_center_button);
	printf("initialize exit");


}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	armLift.set_brake_mode(MOTOR_BRAKE_HOLD);

	resetTrackingWheels();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	forwardPID = createkPID(12.5, 0.1, 2.3);
	turnPID = createkPID(1.75, 0.06, 1.1);
	adjustPID = createkPID(2.0, 0.0, 0.04);
	armPID = createkPID(0.0, 0.0, 0.0);
	driveStep = 0;

	connor();
	//connorRed();
	//setDriveCoast();
	//slopeTest();
	//intakeTest();
	//multipleSubsystemTest();
	//redStackFive();
	//blueStackFive();
	//autonCorrect();
	//scoreTurnLeft();
	//scoreTurnRight();
	//redFiveStack();

	//blueFiveStack();
	//protectedBlue();
	//protectedRed();

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	armLift.set_brake_mode(MOTOR_BRAKE_HOLD);

	while (true) {

		updatePosition();
		pros::lcd::print(6, "A: %f", getAngleDeg());
		setDriveMotors();

		pros::lcd::print(2, "SlopeAngle %f", slopeAngle);
	//	angleTrack();

		setSlopeMotors();

		setIntakeMotors();

		setMacroMotors();

		setAutonButton();

		KpDrive = adjustKp(KpDrive, 0.05);
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) == 1){
			resetPosition();

//			slopeLift.tare_position();
		}


		//pros::lcd::print(0, "armAngle %f", armLift.get_position());
		pros::delay(20);
	}
}
