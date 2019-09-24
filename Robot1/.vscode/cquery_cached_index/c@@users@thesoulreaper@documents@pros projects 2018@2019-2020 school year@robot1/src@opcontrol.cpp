#include "main.h"

void opcontrol() {
	while(true) {
		base.drive();
		lift.drive();
	}
}
