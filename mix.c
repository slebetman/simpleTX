#include "txmod.h"
#include "ppmio.h"

void mix(void)
{
	int channel1_normalized, channel2_normalized, left_servo, right_servo;

	output_pulse[CHANNEL3] = input_pulse[CHANNEL3];
	output_pulse[CHANNEL4] = input_pulse[CHANNEL4];
	
	// V-tail mix:
	channel1_normalized = input_pulse[CHANNEL1]-SERVO_MIN;
	channel2_normalized = input_pulse[CHANNEL2]-SERVO_MIN;
	
	left_servo = (channel1_normalized+channel2_normalized)/2;
	right_servo = (channel1_normalized+(SERVO_MAX-channel2_normalized))/2;
	
	output_pulse[CHANNEL1] = left_servo+SERVO_MIN;
	output_pulse[CHANNEL2] = right_servo+SERVO_MIN;
}
