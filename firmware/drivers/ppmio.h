#define PULSE_MIN 2000 /* (1000*2) */
#define PULSE_MAX 4000 /* (2000*2) */
#define PULSE_CENTER 3000 /* ((PULSE_MIN+PULSE_MAX)/2) */

#define FRAME_TIME 40000 /* (20 * 2000) */

#define stopPPM() TMR1IE=0;TMR1ON=0

extern void startPPM (unsigned short);
extern void processOutput ();
extern void processPPM ();


