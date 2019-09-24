#include "main.h"

Lift::Lift() {
  //LIFT PID ERRORS
  int liftTarget = Lift1.get_position();
  int liftErrorLast = 0;
  int liftError = 0;
  int liftCurr = 0;
  int liftErrorDiff = 0;

  //LIFT PID VARIABLES
  int liftP;
  int liftD;
  int liftI;

  //LIFT PID CONSTANTS
  float liftKp = 0.35;
  float liftKd = 0;
  float liftKi = 0;
  int liftPower = 0;

  //ANGLER PID ERRORS
  int anglerTarget = TrayAngler.get_position();
  int anglerErrorLast = 0;
  int anglerError = 0;
  int anglerCurr = 0;
  int anglerErrorDiff = 0;

  //LIFT PID VARIABLES
  int anglerP;
  int anglerD;
  int anglerI;

  //LIFT PID CONSTANTS
  float anglerKp = 0.85;
  float anglerKd = 0;
  float anglerKi = 0;
  int anglerPower = 0;
}

void Lift::setIntakePower(int power) {
  Roller = power;
}

void Lift::liftPID() {
  //LIFT
  liftCurr = Lift1.get_position();
  liftError = liftTarget - liftCurr;
  liftErrorDiff = liftError - liftErrorLast;
  liftErrorLast = liftError;

  liftP = liftKp * liftError;
  liftD = liftKd * liftErrorDiff;

  liftPower = (liftP + liftD);

  if(liftPower > 127){
    liftPower = 127;
  }
  if(liftPower <- 127){
    liftPower = -127;
  }

  if(second.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < 10 && second.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) > -10) {
    Lift1.move_absolute(liftTarget, 50);
    Lift2.move_absolute(liftTarget, 50);

    //Add Presets
    /*
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)||second.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
     liftTarget = 700;
    }
    else if (second.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
     liftTarget = 500;
    }
    else if (second.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
     liftTarget = 0;
    }
    */
  } else {
    Lift1.move(second.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
    Lift2.move(second.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));
    liftTarget = Lift1.get_position();
  }
}

void Lift::anglerPID() {
  anglerCurr = TrayAngler.get_position();
  anglerError = anglerTarget - anglerCurr;
  anglerErrorDiff = anglerError - anglerErrorLast;
  anglerErrorLast = anglerError;

  anglerP = anglerKp * anglerError;
  anglerD = anglerKd * anglerErrorDiff;

  anglerPower = (anglerP + anglerD);
   if(anglerPower > 127){
     anglerPower = 127;
   }
   if(anglerPower < -127){
     anglerPower = -127;
   }

   //TrayAngler.move(anglerPower);


   if(second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) < 10 && second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) > -10) {
     TrayAngler.move_absolute(anglerTarget, 50);
   } else {
     //if(anglerLimit.get_value() == 1 && -second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) < 0) {
    //    TrayAngler.move(0);
     //}
     TrayAngler.move(-second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
     anglerTarget = TrayAngler.get_position();
   }
   //SET PRESETS
   /*
   if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)||second.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) { //if L1 button is pressed
      anglerTarget = 0;//move roller full power
   }
   else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)||second.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){//in
      anglerTarget = -350;
   }
   else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)||second.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){//in
      anglerTarget = 400;
   }
   else if (second.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){//in
      anglerTarget = -700;
   }*/
}

void Lift::drive() {
  liftPID();
  anglerPID();

  if(master.get_digital(E_CONTROLLER_DIGITAL_UP) || second.get_digital(E_CONTROLLER_DIGITAL_R1)) {
    setIntakePower(127);
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN) || second.get_digital(E_CONTROLLER_DIGITAL_L1)) {
    setIntakePower(-127);
  } else {
    setIntakePower(0);
  }
}
