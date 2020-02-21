#include "main.h"


std::shared_ptr<OdomChassisController> chassis = ChassisControllerBuilder()
    .withMotors({flPort, blPort}, {frPort, brPort})

    .withDimensions(AbstractMotor::gearset::green, {{4_in, 10_in}, imev5GreenTPR})
    .withSensors(okapi::ADIEncoder{'B', 'C'}, okapi::ADIEncoder{'D', 'E', true})
    .withOdometry({{2.75_in, 10.4_in}, quadEncoderTPR}, StateMode::FRAME_TRANSFORMATION) // use the same scales as the chassis (above)
    .buildOdometry(); // build an odometry chassis

void flipOut() {
  LiftM.move(-127);
  pros::delay(600);
  LiftM.move(127);
  pros::delay(600);
  LiftM.move(0);
}

void driveBumper() {
  while(true) {
    if(placeBump.get_value() == 0) {
      FL.move_velocity(70);
      BL.move_velocity(70);
      FR.move_velocity(70);
      BR.move_velocity(70);
    } else {
      FL.move_velocity(0);
      BL.move_velocity(0);
      FR.move_velocity(0);
      BR.move_velocity(0);
      break;
    }
  }
}

void blueProtected() {
    flipOut();
    lift.setIntakePower(127);

    base.pidDrive(-1, 400, 1200, 127);
    base.pidDrive(1, 200, 1000, 127);
    base.pidStrafe(-1, 700, 1000, 127);
    base.pidDrive(1, 500, 1000, 127);
    base.pidStrafe(1, 200, 700, 127);
    base.pidDrive(1, 500, 1000, 127);
    base.pidTurn(-1, 350, 1000, 127);
    base.pidDrive(1, 1300, 1200, 127);
    base.pidTurn(-1, 650, 1200, 127);
    base.pidDrive(1, 1500, 3000, 70);
}

void redProtected() {
  flipOut();
  lift.setIntakePower(127);

  base.pidDrive(-1, 500, 1200, 127);
  base.pidDrive(1, 200, 1000, 127);
  base.pidStrafe(1, 700, 1000, 127);
  base.pidDrive(1, 500, 1000, 127);
  base.pidStrafe(-1, 200, 700, 127);
  base.pidDrive(1, 500, 1000, 127);
  base.pidTurn(1, 350, 1000, 127);
  base.pidDrive(1, 1300, 1200, 127);
  base.pidTurn(1, 650, 1200, 127);
  base.pidDrive(1, 1500, 3000, 70);
}

void redUnprotected() {

  /*flipOut();

  lift.setIntakePower(127);
  pros::delay(600);
  //autoTopCube = true;
  base.pidDrive(1, 1800, 1400, 100);
  lift.movePos(750, 600);
  base.pidDrive(1, 500, 500, 110);
  resetLift = true;
  pros::delay(600);
  base.pidTurn(left, 625, 1000,127);

  base.pidDrive(-1, 2755, 1500, 127);
  base.pidTurn(right, 600, 800, 127);
  base.lineUp(500, 127, 200);
  base.pidDrive(1, 2700, 2500, 80);
  base.lineUp(1800, 127, 200);
  base.pidTurn(right, 1000, 1000, 127);
  multiPlace = true;
  base.pidStrafe(right, 800, 800, 127);
  driveBumper();*/

/*
  //flipOut();
  lift.setIntakePower(127);
  pros::delay(1000);
  base.pidDriveUltra(1, 680, 682, 1400, 100); //550, 555

  //autoTopCube = true;
  slowOutTake = true;
  lift.movePos(500, 750);
  //tray.movePos(975, 700);
  lift.setIntakePower(127);
  base.pidDrive(1, 800, 900, 60);
  resetLift = true;*/

  flipOut();
  lift.setIntakePower(127);
  pros::delay(1000);
  base.lineUp(500, 127, 100);
  base.pidDriveUltra(1, 680, 682, 1400, 100); //550, 555

  base.pidTurn(left, 720, 1000,127);
  base.pidDrive(-1, 2600, 1500, 127);
  base.pidTurn(right, 700, 800, 127);
  base.lineUp(500, 127, 200);
  base.pidDrive(1, 2400, 2500, 80);
  //base.pidStrafe(left, 800, 1000, 127);
  //base.pidDrive(1,500, 1000, 127);
  base.lineUp(1800, 127, 300);
  base.pidTurn(right, 1000, 1000, 127);
  multiPlace = true;
  base.pidStrafe(right, 1000, 900, 127);
  driveBumper();

  //autoTopCube = true;

}

void blueUnprotected() {
    flipOut();

    lift.setIntakePower(127);

      /*
        base.pidDrive(1, 800, 1400, 127);
        base.pidDrive(-1, 900, 1400, 127);
        //base.pidDrive(1, 50, 00, 127);
        base.pidStrafe(-1, 1000, 1800, 127);
        base.pidDrive(-1, 250, 500, 127);

        */
    base.pidDrive(1, 1000, 2000, 80);

      //  base.pidTurn(1, 200, 1000, 127);

      //  base.pidDrive(1, 300, 1000, 127);
    //    base.pidTurn(-1, -200, 1000, 127);

    base.pidDrive(-1, 950, 1000, 127);
      //  base.pidDrive(-1, 200, 500, 90);
    lift.setIntakePower(0);
    base.pidTurn(1, 440, 1000, 127);

    base.pidStrafe(1, 650, 750, 127);
    base.pidDrive(1, 200, 500, 127);
    multiPlace = true;
    pros::delay(3200);
    base.pidDrive(-1, 500, 1000, 127);
}



void moveLiftPos(int speed, int timeOut) {
  //LiftM.tare_position();
  int timeStamp = pros::millis();
  int netTime = 0;
  while(netTime < timeOut) {
    netTime = pros::millis() - timeStamp;
    LiftM = speed;
    //delay(50);
  }
  LiftM = 0;
}


void skillsAuto() {
  flipOut();

//  slowOutTake = true;
  lift.movePos(1495, 1000);
  base.pidDrive(forward, 850, 1500, 127);
  lift.setIntakePower(-90);
  pros::delay(800);
  base.lineUp(2000, 127, 100);
}


void autonomous() {

  FL.set_brake_mode(E_MOTOR_BRAKE_COAST);
  FR.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BL.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BR.set_brake_mode(E_MOTOR_BRAKE_COAST);
  redUnprotected();
  //base.pidDriveUltra(1, 545, 555, 10000, 127);

  //base.pidIMUTurn(left, 270, 1000, 127);
//  redUnprotected();
//  moveLiftPos(-127, 1000);
/*
  base.pidDrive(1, 250, 1000, 127);
  LiftM = -127;
  pros::delay(1000);
  LiftM = 127;
  pros::delay(1400);
  LiftM = 0;

  lift.setIntakePower(127);


  base.pidDrive(1, 800, 1400, 127);
  base.pidDrive(-1, 900, 1400, 127);
  //base.pidDrive(1, 50, 00, 127);
  base.pidStrafe(-1, 1000, 1800, 127);
  base.pidDrive(-1, 250, 500, 127);


  base.pidDrive(1, 1100, 1700, 90);


  base.pidDrive(-1, 950, 1500, 127);
  lift.setIntakePower(0);
  base.pidTurn(-1, 400, 1000, 127);
  multiPlace = true;
  base.pidStrafe(-1, 600, 1100, 127);
  base.pidDrive(1, 200, 1500, 127);
  pros::delay(1200);
  base.pidDrive(-1, 500, 1000, 127);

*/

  //  moveLiftPos(-127, 1000);


}
