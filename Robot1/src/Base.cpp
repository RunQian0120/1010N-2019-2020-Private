#include "main.h"

Base::Base() {
  direction = 1;
}

void Base::resetEncoder() {
  L.tare_position();
  R.tare_position();
  L2.tare_position();
  R2.tare_position();
}

void Base::setLeftPower(int power) {
  L = power;
  L2 = power;
}

void Base::setRightPower(int power) {
  R = power;
  R2 = power;
}

void Base::pidDrive(int target, int timeout, float kp, float kd, float skew, int speedCap) {
    R.tare_position();
    L.tare_position();

    int encoderAverage = 0;
    int startTime = pros::millis();
    int netTime = 0;
    int errorDiff = 0;
    int errorLast = 0;
    int error = target;

    while( (netTime < timeout)) {

      netTime  = pros::millis() - startTime;

      encoderAverage = abs(R.get_position())+ abs(L.get_position()/2);
      int encoderError = R.get_position() - L.get_position(); //subtract from R side

      int error = target - encoderAverage;

       errorDiff = error - errorLast;

       errorLast = error;

      int p = kp*error;
      int d = kd*errorDiff;

       int motorPower = (p+d);
       if(motorPower>speedCap){
         motorPower = speedCap;
       }
       if(motorPower<-speedCap){
         motorPower =-speedCap;
       }


       int rightPower = motorPower - (skew*encoderError);
       int leftPower = motorPower + (skew*encoderError);

       R.move(rightPower);
       R2.move(rightPower);

       L.move(leftPower);
       L2.move(leftPower);


      }
      R.move(0);
      L.move(0);
      R2.move(0);
      L2.move(0);

}

void Base::pidTurn(int target, int timeout, float kp, float kd, int speedCap){
    R.tare_position();

    int encoderAverage = 0;
    int startTime = pros::millis();
    int netTime = 0;
    int errorDiff = 0;
    int errorLast = 0;
    int error = target;

    while((netTime < timeout)){

      netTime  = pros::millis() - startTime;

      encoderAverage = R2.get_position();

      int error = target - encoderAverage;

       errorDiff = error - errorLast;
       errorLast = error;

      int p = kp*error;
      int d = kd*errorDiff;

       int motorPower = (p+d);
       if(motorPower>speedCap){
         motorPower = speedCap;
       }
       if(motorPower<-speedCap){
         motorPower =-speedCap;
       }

       R.move(motorPower);
       R2.move(motorPower);

       L.move(motorPower);
       L2.move(motorPower);
      }
      R.move(0);
      L.move(0);
      R2.move(0);
      L2.move(0);
}



int expDrive (int joyVal, float driveExp, int joyDead, int motorMin) {
    int joySign;
    int joyMax = 127 - joyDead;
    int joyLive = abs(joyVal) - joyDead;
    if (joyVal > 0) {joySign = 1;}
    else if (joyVal < 0) {joySign = -1;}
    else {joySign = 0;}
    int power = joySign * (motorMin + ((100 - motorMin) * pow(joyLive, driveExp) / pow(joyMax, driveExp)));
    return power;
}

void Base::drive() {
  const int cJoyDead = 8;
  const int cMotorMin = 15;
  const float cDriveExp = 1.4;

  int Y1 = expDrive(-master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), cDriveExp, cJoyDead, cMotorMin);
  int X1 = expDrive(-master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X), cDriveExp, cJoyDead, cMotorMin);

  setLeftPower(Y1+X1);
  setRightPower(Y1-X1);


  /*
  if(second.get_digital(E_CONTROLLER_DIGITAL_A)) {
    moveOutS = 1;
  } else if(second.get_digital(E_CONTROLLER_DIGITAL_B)) {
    //moveOutS = 0;
    moveOutTime = 0;
  }
  //lcd::initialize();
  lcd::print(0,"MoveOutTime: %d", moveOutTime);
  lcd::print(1,"MoveOutS: %d", moveOutS);
  if(moveOutS == 1) {
    setLeftPower(63);
    setRightPower(63);
    //lift.setIntakePower(-63);
    moveOutTime += 1;
  }


  if(moveOutTime >= moveOutTimeCap) {
    moveOutS = 0;
    moveOutTime = 0;
  }*/
}
