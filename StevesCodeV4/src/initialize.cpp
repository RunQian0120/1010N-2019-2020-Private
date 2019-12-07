#include "main.h"

pros::Motor FR(frPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
pros::Motor BR(brPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
pros::Motor FL(flPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor BL(blPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

pros::Controller master (E_CONTROLLER_MASTER);
pros::Controller partner (E_CONTROLLER_PARTNER);

pros::Motor LiftM(liftPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);

pros::Motor Intake1(intake1Port, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
pros::Motor Intake2(intake2Port, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);

pros::Motor TrayM(trayPort, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_COUNTS);

bool multiAutonomousBool = false;

Base base;
Lift lift;
Tray tray;

pros::ADIDigitalIn anglerLimit('c');
pros::ADIDigitalIn liftLimit('f');
pros::ADIDigitalIn placeBump('d');
pros::ADIAnalogIn placeLight('e');
pros::ADIEncoder encoderR('a','b', false);
pros::ADIEncoder encoderL('g','h', true);

void multiAutonomous(void*param) {
  while(pros::competition::is_autonomous()) {
    if(multiAutonomousBool == true) {
      while (placeLight.get_value() > 2000) {
        lift.setIntakePower(63);
      }
      int time = pros::millis(); //Current Timestamp
      int netTime = 0;
      while(netTime < 3000) { //Sets timeout to 3 seconds
        netTime = pros::millis() - time;
        if(TrayM.get_position() > -1200) { //Sets boundaries for fast movement using encoder position
          TrayM = -127;
        } else if(TrayM.get_position() <= -1200 && TrayM.get_position() > -1800) { //Changes speeds based on encoder positions
          TrayM = -80;
        } else if (TrayM.get_position() <= -1800 && TrayM.get_position() > -2500) {
          TrayM = -60;
        }

        if(TrayM.get_position() <= -2500) { //Tops the place if target position of tray is hit
          break;
        }
      }
      TrayM = 0;
      multiAutonomousBool = false;
    }
    delay(10);
  }
}

void initialize() {
  //multiAutonomousBool = false;
  Task multiAuton(multiAutonomous, (void*)"PROS",
    TASK_PRIORITY_DEFAULT,
    TASK_STACK_DEPTH_DEFAULT,
    "Test1"
  );

  pros::lcd::initialize();
  pros::lcd::print(0, "Hello");

  TrayM.tare_position();
  LiftM.tare_position();
  base.resetEncoder();
  encoderR.reset();
  encoderL.reset();

  FL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  FR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  BR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  LiftM.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  TrayM.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  Intake1.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  Intake2.set_brake_mode(E_MOTOR_BRAKE_HOLD);

}
