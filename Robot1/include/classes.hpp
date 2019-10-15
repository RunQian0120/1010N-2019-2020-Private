
#ifndef _CLASSES_HPP_
#define _CLASSES_HPP_

class Base {
public:
    Base(); // Constructor
    void drive(); //opdrive function

    void setRightPower(int power);
    void setLeftPower(int power);

    void pidDrive(int target, int timeout, float kp, float kd, int speedCap);
    void pidTurn(int target, int timeout, float kp, float kd, int speedCap);

    void resetEncoder();
    int direction;

//private:
};

class Lift {
public:
  //Constructor
  Lift();
  //Drive function
  void drive();
  //PID LIFT + ANGLER
  void liftPID(int speedCap);
  void anglerPID(int speedCap);

  int liftTarget;
  int anglerTarget;

  //void moveOutTake();

  void setIntakePower(int power);

  void autoPlace();

  void driverPlace();
private:
  //LIFT PID ERRORS
  int liftErrorLast;
  int liftError;
  int liftCurr;
  int liftErrorDiff;

  //LIFT PID VARIABLES
  int liftP;
  int liftD;
  int liftI;

  //LIFT PID CONSTANTS
  float liftKp;
  float liftKd;
  float liftKi;
  int liftPower;

  //ANGLER PID ERRORS
  int anglerErrorLast;
  int anglerError;
  int anglerCurr;
  int anglerErrorDiff;

  //LIFT PID VARIABLES
  int anglerP;
  int anglerD;
  int anglerI;

  //LIFT PID CONSTANTS
  float anglerKp;
  float anglerKd;
  float anglerKi;
  int anglerPower;


  int placeS;
  int placeTimer;
  bool moveOutS;
};
#endif
