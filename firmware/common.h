/* Assumes PIC18F2520 running at 32MHz */

#include "pinout.h"

#ifndef _COMMON_H_
#define _COMMON_H_

#define enableInterrupts() GIE=1
#define disableInterrupts() GIE=0

extern unsigned char tick;
extern unsigned char frameTimer;
#define TICK_1MS 6
#define TICK_ANALOG_SAMPLE 63500
#define resetTick() tick=0;TMR0=TICK_1MS

#endif