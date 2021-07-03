#include "analog-const.h"

extern short analog_count;

extern void analog_init ();
extern unsigned short analog_get (unsigned char channel);
extern unsigned short analog_get_sync (unsigned char channel);
extern void analog_timer_interrupt_handler ();

