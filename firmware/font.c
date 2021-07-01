
extern const unsigned char smallFont[95*5];

#include "font-fixed.h"

const unsigned char* getFontIndex (unsigned char ch) {
	int idx;
	
	idx = ch-32;
	
	if (idx < 0 || idx >= 95 ) {
		idx = 0;
	}
	
	idx *= 5;
	
	return &smallFont[idx];
}

int string2pixels (const char* txt, unsigned char* buffer, int bufferLength) {
	int i, j;
	const unsigned char* font;
	
	for (i=0;i<bufferLength;) {
		if (*txt == 0x00) break;
		
		font = getFontIndex(*txt);
		txt++;
		
		for (j=0;j<5;j++) {
			if (font[j] == 0xff) break;
			buffer[i] = font[j];
			i++;
		}

		buffer[i] = 0x00;
		i++;
	}
	
	return i;
}
