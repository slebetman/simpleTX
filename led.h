#include "ledfont.h"

//########################################################################
// PROTOTYPES FOR 7 SEGMENT LED FUNCTIONS
//########################################################################
extern void ledSend(unsigned char data);
extern void ledSendBcd(unsigned char data);
extern void addBcd(char* hi, char* lo, const char datahi, const char datalo);
extern unsigned char char2bcd(unsigned char data);

#define ledSendHex(x) ledSendBcd(x)
