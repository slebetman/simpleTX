
extern const unsigned char smallFont[95*5];

#include "font-small.h"

const unsigned char* getFontIndex (unsigned char ch) {
	signed char idx;
	
	idx = ch-32;
	
	if (idx < 0 || idx >= 95 ) {
		idx = 0;
	}
	
	idx *= 5;
	
	return smallFont + idx;
}
