#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_


#define PROS_USE_SIMPLE_NAMES


#define PROS_USE_LITERALS

#include "api.h"
#include "classes.hpp"
using namespace pros;

//Defining Motors
extern Motor R;
extern Motor L;
extern Motor R2;
extern Motor L2;
extern Motor Lift1;
extern Motor Roller1;
extern Motor Roller2;
extern Motor TrayAngler;

extern ADIDigitalIn anglerLimit;

//Definign Controllers
extern Controller master;
extern Controller second;

//Class definition
extern Base base;
extern Lift lift;

//Defining Ports
#define rPort 15
#define lPort 18
#define r2Port 20
#define l2Port 11
#define liftPort 5
#define rollerPort1 4
#define rollerPort2 1
#define anglerPort 2


#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

#endif  // _PROS_MAIN_H_
