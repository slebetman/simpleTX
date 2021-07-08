#define PULSE_MIN 6256
#define PULSE_MAX 11620
#define PULSE_CENTER ((PULSE_MIN+PULSE_MAX)/2)
#define SERVO_RANGE (PULSE_MAX-PULSE_MIN)
#define SERVO_MAX (SERVO_RANGE/2)
#define SERVO_MIN -SERVO_MAX

#define stopPPM() TMR1IE=0;TMR1ON=0

// Use to signal modes for startPPM and startCapture:
#define BEGIN 0
#define CONTINUE 1

extern void startPPM (unsigned short, signed char);
extern void processOutput ();


