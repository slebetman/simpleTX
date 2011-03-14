/* Assumes PIC16F690 running at 24MHz */

#define SERVO_MIN 6256
#define SERVO_MAX 11620
#define SERVO_CENTER ((SERVO_MIN+SERVO_MAX)/2)
#define SERVO_RANGE (SERVO_MAX-SERVO_MIN)

#define TOTAL_OUTPUT_CHANNELS 6
#define TOTAL_INPUT_CHANNELS 4

struct twoBytes {
	unsigned char low;
	unsigned char high;
};

union intOrBytes {
	unsigned int integer;
	struct twoBytes bytes;
};

extern union intOrBytes input_pulse[TOTAL_INPUT_CHANNELS];
extern union intOrBytes output_pulse[TOTAL_OUTPUT_CHANNELS];
