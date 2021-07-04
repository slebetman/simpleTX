#ifndef _ANALOG_
#define _ANALOG_

#include "analog-const.h"

extern short analog_count;

extern void init_analog ();
extern unsigned short analog_get (unsigned char channel);
extern unsigned short analog_get_sync (unsigned char channel);
extern void analog_timer_interrupt_handler ();

#endif
