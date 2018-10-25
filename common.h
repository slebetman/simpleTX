/* Assumes PIC16F690 running at 24MHz */

#include "pinout.h"

#ifndef _COMMON_H_
#define _COMMON_H_

#define enableInterrupts() GIE=1
#define disableInterrupts() GIE=0

extern unsigned char tick;
extern unsigned char frameTimer;
#define TICK_1MS 70
#define resetTick() tick=0;TMR0=TICK_1MS

#endif