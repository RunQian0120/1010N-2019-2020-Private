#include "main.h"

Base::Base() {

}

void Base::drive() {
  int Y = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  int X = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
  int Z = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
  FR = Y - X - Z;
  BR = Y - X + Z;
  FL = Y + X + Z;
  BL = Y + X - Z;
}
