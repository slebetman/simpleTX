#include "txmod.h"

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
