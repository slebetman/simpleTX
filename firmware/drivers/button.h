#ifndef _BUTTON_
#define _BUTTON_

#include "button-const.h"

extern void button_init (button *btn, unsigned char id);
extern unsigned char button_click (button *btn);
extern unsigned char button_long_click (button *btn);

#endif