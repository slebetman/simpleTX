#include <xc.h>
#include "ppmio.h"
#include "common.h"
#include "analog.h"

void interrupt HANDLER(void)
{
	if (TMR1IF)
	{
		processOutput();
		TMR1IF = 0;
	}
	if (TMR3IF)
	{
		TMR3 = TICK_5US;
		analog_timer_interrupt_handler();
		TMR3IF = 0;
	}
	if (TMR0IF)
	{
		TMR0 = TICK_1MS;
		TMR0IF = 0;   // reset timer interrupt
		tick ++;
		frameTimer ++;
	}
}

