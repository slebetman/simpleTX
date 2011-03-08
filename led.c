#include <pic.h>
#include "ledfont.h"
#include "pinout.h"

//########################################################################
// 7 SEGMENT LED FUNCTIONS
//########################################################################
void ledSend(unsigned char data)
{
	char i;
	for(i=0;i<8;i++)
	{
		if(data & 0x80){
			LED_DATA = 0;
		} else {
			LED_DATA = 1;
		}
		LED_CLOCK = 1;
		data <<= 1;
		LED_CLOCK = 0;
	}
}

void ledSendBcd(unsigned char data)
{
	unsigned char temp;
	temp = data & 0xf0;
	temp >>= 4;
	if(temp==0x0f) {
		temp++;
	}
	ledSend(font[temp]);
	temp = data & 0x0f;
	ledSend(font[temp] DOT); // send dot anyway since the dots
	                         // for decimal are not wired ;-)
}

void addBcd(char* hi, char* lo, const char datahi, const char datalo)
{
	*lo += datalo;
	if(*lo >= 10)
	{
		*lo -= 10;
		*hi += 1;
	}
	*hi += datahi;
}

unsigned char char2bcd(unsigned char data)
{
	char ret = 0;
	char temp = 0;
	
	if (data & 0x01) {
		addBcd(&temp, &ret, 0, 1);
	}
	if (data & 0x02) {
		addBcd(&temp, &ret, 0, 2);
	}
	if (data & 0x04) {
		addBcd(&temp, &ret, 0, 4);
	}
	if (data & 0x08) {
		addBcd(&temp, &ret, 0, 8);
	}
	if (data & 0x10) {
		addBcd(&temp, &ret, 1, 6);
	}
	if (data & 0x20) {
		addBcd(&temp, &ret, 3, 2);
	}
	if (data & 0x40) {
		addBcd(&temp, &ret, 6, 4);
	}
	temp <<= 4;
	ret |= temp;
	return ret;
}

