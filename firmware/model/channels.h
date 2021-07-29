#ifndef _CHANNELS_
#define _CHANNELS_

#include "channels-const.h"
#include "../drivers/analog.h"

extern short channels[TOTAL_CHANNELS];
extern short output_channels[TOTAL_OUTPUT_CHANNELS];
extern short center[TOTAL_ANALOG_CHANNELS-1];

#endif
