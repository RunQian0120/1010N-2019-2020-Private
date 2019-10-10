#include "main.h"

void opcontrol() {
	while(true) {
		base.drive();
		lift.drive();
		pros::delay(5);
	}
}
