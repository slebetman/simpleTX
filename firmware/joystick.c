#include <xc.h>
#include <stdlib.h>
#include "analog.h"

#define JOYSTICK_REFRESH 10
#define JOYSTICK_INIT    50

bit center_calibrated = 0;
bit joystick_active = 0;

unsigned short center_calibration[2];
int joystick_values[2];
unsigned short timer;

void joystick_init () {
	center_calibrated = 0;
	joystick_active = 0;
	timer = 0;
}

void deadband (int *value, int bandwidth) {
	if (abs(*value) < bandwidth) {
		*value = 0;
	}
}

void joystick_timer_interrupt_handler () {
	timer++;
	
	if (!center_calibrated) {
		if (timer > JOYSTICK_INIT) {
			center_calibration[0] = analog_values[0];
			center_calibration[1] = analog_values[1];
			
			center_calibrated = 1;
		}
	}
	else {
		joystick_values[0] = analog_values[0] - center_calibration[0];
		joystick_values[1] = analog_values[1] - center_calibration[1];
		
		deadband(&joystick_values[0], 10);
		deadband(&joystick_values[1], 10);
		
		joystick_active = 1;
	}
}
