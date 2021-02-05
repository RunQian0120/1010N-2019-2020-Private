#include "main.h"

// Motor Definitions
pros::Motor FR(frPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor BR(brPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor FL(flPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
pros::Motor BL(blPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

pros::Motor IntakeR(intakeRPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
pros::Motor IntakeL(intakeLPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor RollerTop(rollerTopPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor RollerBot(rollerBotPort, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);


pros::Controller master(E_CONTROLLER_MASTER);

Base base;

void initialize() {
	FR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	BR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	FL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	BL.set_brake_mode(E_MOTOR_BRAKE_HOLD);

}

void autonomous() {
	RollerTop = 127;
	RollerBot = 127;
	pros::delay(5000);
	RollerTop = 0;
	RollerBot = 0;

}


void opcontrol() {
	while(true) {
		base.drive();
		pros::delay(10);

		if(master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			IntakeR = 127;
			IntakeL = 127;
		} else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
			IntakeR = -127;
			IntakeL = -127;
		} else {
			IntakeR = 0;
			IntakeL = 0;
		}

		if(master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
			RollerTop = -127;
			RollerBot = -127;
		}else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
			RollerTop = 127;
			RollerBot = 127;
		} else {
			RollerTop = 0;
			RollerBot = 0;
		}

	}

}
