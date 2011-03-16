#include "txmod.h"
#include "ppmio.h"

void mix(void)
{
	int channel1_normalized, channel2_normalized, channel1_reverse,
		left_servo, right_servo;

	output_pulse[CHANNEL3] = input_pulse[THROTTLE];
	output_pulse[CHANNEL4] = input_pulse[RUDDER];
	
	// V-tail mix:
	channel2_normalized = input_pulse[ELEVATOR]-SERVO_MIN;
	channel1_normalized = input_pulse[AILERON]-SERVO_MIN;
	channel1_reverse = SERVO_RANGE-channel1_normalized;
	
	left_servo = (channel2_normalized+channel1_normalized)/2;
	right_servo = (channel2_normalized+channel1_reverse)/2;
	
	output_pulse[CHANNEL1] = left_servo+SERVO_MIN;
	output_pulse[CHANNEL2] = right_servo+SERVO_MIN;
}
