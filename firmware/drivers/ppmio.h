#define PULSE_MIN (1000*2)
#define PULSE_MAX (2000*2)
#define PULSE_CENTER ((PULSE_MIN+PULSE_MAX)/2)

#define stopPPM() TMR1IE=0;TMR1ON=0

// Use to signal modes for startPPM and startCapture:
#define BEGIN 0
#define CONTINUE 1

extern void startPPM (unsigned short, signed char);
extern void processOutput ();
extern unsigned char processPPM ();


