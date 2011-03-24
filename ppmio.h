#define SERVO_MIN 6256
#define SERVO_MAX 11620
#define SERVO_CENTER ((SERVO_MIN+SERVO_MAX)/2)
#define SERVO_RANGE (SERVO_MAX-SERVO_MIN)

#define TOTAL_OUTPUT_CHANNELS 6
#define TOTAL_INPUT_CHANNELS 5

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

#define stopCapture() CCP1IE=0;CCP1CON=0x00
#define stopPPM() TMR1IE=0;TMR1ON=0

// Use to signal modes for startPPM and startCapture:
#define BEGIN 0
#define CONTINUE 1

extern void syncPPM (void);
extern void startPPM (unsigned int,signed char);
extern void startCapture (signed char);

extern bit in_sync;
extern bit input_done;

extern unsigned int input_pulse[TOTAL_INPUT_CHANNELS];
extern unsigned int output_pulse[TOTAL_OUTPUT_CHANNELS];
