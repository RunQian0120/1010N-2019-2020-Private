#include "main.h"

Motor L(lPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor R(rPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor L2(l2Port, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor R2(r2Port, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor Roller1(rollerPort1, E_MOTOR_GEARSET_06, false,  E_MOTOR_ENCODER_DEGREES);
Motor Roller2(rollerPort2, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);

Motor Lift1(liftPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor TrayAngler(anglerPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

Controller master(E_CONTROLLER_MASTER);
Controller second(E_CONTROLLER_PARTNER);

ADIDigitalIn anglerLimit(1);

Base base;
Lift lift;

void initialize() {
    pros::lcd::initialize();
    pros::lcd::print(0,"HELLO");
    TrayAngler.tare_position();
    Lift1.tare_position();

    L.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    R.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    L2.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    R2.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}
