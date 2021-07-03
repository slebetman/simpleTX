#define PULSE_MIN 6256
#define PULSE_MAX 11620
#define PULSE_CENTER ((PULSE_MIN+PULSE_MAX)/2)
#define SERVO_RANGE (PULSE_MAX-PULSE_MIN)
#define SERVO_MAX (SERVO_RANGE/2)
#define SERVO_MIN -SERVO_MAX

#define TOTAL_OUTPUT_CHANNELS 3
#define TOTAL_INPUT_CHANNELS 3

#define CHANNEL1 0
#define CHANNEL2 1
#define CHANNEL3 2
#define CHANNEL4 3
#define CHANNEL5 4
#define CHANNEL6 5

#define AILERON  input_pulse[CHANNEL1]
#define ELEVATOR input_pulse[CHANNEL2]
#define THROTTLE input_pulse[CHANNEL3]
#define RUDDER   input_pulse[CHANNEL4]

#define stopPPM() TMR1IE=0;TMR1ON=0

// Use to signal modes for startPPM and startCapture:
#define BEGIN 0
#define CONTINUE 1

extern void startPPM (unsigned short, signed char);
extern void processOutput ();

extern short output_pulse[TOTAL_OUTPUT_CHANNELS];

