#include "main.h"

Lift::Lift() {
  //LIFT PID ERRORS
  liftTarget = Lift1.get_position();
  liftErrorLast = 0;
  liftError = 0;
  liftCurr = 0;
  liftErrorDiff = 0;

  //LIFT PID VARIABLES
  liftP;
  liftD;
  liftI;

  //LIFT PID CONSTANTS
  liftKp = 0.5;
  liftKd = 0;
  liftKi = 0;
  liftPower = 0;

  //ANGLER PID ERRORS
  anglerTarget = TrayAngler.get_position();
  anglerErrorLast = 0;
  anglerError = 0;
  anglerCurr = 0;
  anglerErrorDiff = 0;

  //LIFT PID VARIABLES
  anglerP;
  anglerD;
  anglerI;

  //LIFT PID CONSTANTS
  anglerKp = .85;
  anglerKd = 0.0;
  anglerKi = 0.0;
  anglerPower = 0;

}

void Lift::setIntakePower(int power) {
  Roller1 = power;
  Roller2 = power;
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
  if(liftPower < -127){
    liftPower = -127;
  }

  if(second.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) < 10 && second.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y) > -10) {
    Lift1.move(liftPower);

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

  anglerPower = anglerP + anglerD;

  if(anglerPower > 127){
   anglerPower = 127;
  }
  if(anglerPower < -127){
   anglerPower = -127;
  }

  //TrayAngler.move(anglerPower);


   if(anglerLimit.get_value() == 0) {
     if(second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) < 10 && second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) > -10) {
       TrayAngler.move(anglerPower);
       //TrayAngler.move_absolute(anglerTarget, 75);
     } else {
       TrayAngler.move(-second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
       anglerTarget = TrayAngler.get_position();
     }
   } else if (anglerLimit.get_value() == 1) {
     if(second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) < 10) {
       //TrayAngler.move_absolute(anglerTarget, 75);
       TrayAngler.move(anglerPower);
     } else {
       if(second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) >= 10) {
         TrayAngler.move(-second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
         anglerTarget = TrayAngler.get_position();
       }
     }
   }


   /*
   if(second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) < 10 && second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) > -10) {
     TrayAngler.move_absolute(anglerTarget, 50);
   } else {
     //TrayAngler.move(-second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
     //anglerTarget = TrayAngler.get_position();
     if(anglerLimit.get_value() == 1) {
        if(second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) > -10 && second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) < 10) {
          TrayAngler.move_absolute(anglerTarget, 50);
        } else if (second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) < -10) {
          TrayAngler.move(-second.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
          anglerTarget = TrayAngler.get_position();
        }
     }
   }*/

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

/*
void Lift:: moveOutTake () {
  if(second.get_digital(E_CONTROLLER_DIGITAL_A)) {
    moveOutS = true;
  } else if(second.get_digital(E_CONTROLLER_DIGITAL_B)) {
    moveOutS = false;
    moveOutTime = 0;
  }
  //lcd::initialize();
  lcd::print(0,"MoveOutTime: %d", moveOutTime);
  lcd::print(1,"MoveOutS: %d", moveOutS);
  if(moveOutS == 1) {
    //base.setLeftPower(63);
    //base.setRightPower(63);
    //lift.setIntakePower(-63);
    moveOutTime += 1;
  }
  if(moveOutTime >= 1500) {
    moveOutS = false;
    moveOutTime = 0;
  }

}*/

void Lift::drive() {
  liftPID();
  anglerPID();

  //moveOutTake();

  if(master.get_digital(E_CONTROLLER_DIGITAL_R1) || second.get_digital(E_CONTROLLER_DIGITAL_R1)) {
    setIntakePower(127);
  } else if(master.get_digital(E_CONTROLLER_DIGITAL_L1) || second.get_digital(E_CONTROLLER_DIGITAL_L1)) {
    setIntakePower(-127);
  } else {
    setIntakePower(0);
  }
}
