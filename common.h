/* Assumes PIC16F690 running at 24MHz */

#include pinout.h

#ifndef _COMMON_H_
#define _COMMON_H_

#define enableInterrupts() GIE=1
#define disableInterrupts() GIE=0

#define SERVO_MIN 6256
#define SERVO_MAX 11620
#define SERVO_CENTER ((SERVO_MIN+SERVO_MAX)/2)
#define SERVO_RANGE (SERVO_MAX-SERVO_MIN)

#define TOTAL_OUTPUT_CHANNELS 6
#define TOTAL_INPUT_CHANNELS 5

#define CHANNEL1 0
#define CHANNEL2 1
#define CHANNEL3 2
#define CHANNEL4 3
#define CHANNEL5 4
#define CHANNEL6 5

#define AILERON  CHANNEL1
#define ELEVATOR CHANNEL2
#define THROTTLE CHANNEL3
#define RUDDER   CHANNEL4

extern unsigned char tick;
#define TICK_1MS 70
#define resetTick() tick=0;TMR0=TICK_1MS

#endif