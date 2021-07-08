#include "channels.h"

extern bit trim_mode;
extern short input_trim[TOTAL_ANALOG_CHANNELS];
extern short stick_center[TOTAL_ANALOG_CHANNELS];

#define NO_EXCEPTIONS -1
#define EXCEPT
extern void trim (unsigned char on_switch, signed char exception);
extern void initTrim (void);
extern void setTrimSlot (char slot);