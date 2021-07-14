#include "channels.h"

#define NAME_SIZE          10
#define NAME_OFFSET        0
#define TRIM_OFFSET        (NAME_OFFSET+NAME_SIZE)
#define EXT_RANGE_OFFSET   (TRIM_OFFSET+1)
#define OUTPUT_MAP_OFFSET  (EXT_RANGE_OFFSET+4)
#define MIX_OFFSET         (OUTPUT_MAP_OFFSET+3)

#define MAX_MIXES   11
#define MIX_SIZE    3
#define MODEL_SIZE  (MIX_OFFSET+(MIX_SIZE*MAX_MIXES))
#define MAX_MODELS  4

#define REVERSE_MASK 0x20

#define COND_NONE    0x00
#define COND_A_UP    0x01
#define COND_A_MID   0x02
#define COND_A_DOWN  0x03
#define COND_B_UP    0x04
#define COND_B_MID   0x05
#define COND_B_DOWN  0x06

struct mix {
	unsigned char input;
	unsigned char output;
	signed char scale;
	signed char expo;
	unsigned char conditional;
	unsigned char reverse; // true/false
};

struct extendedRangeBits {
	unsigned ch0:1;
	unsigned ch1:1;
	unsigned ch2:1;
	unsigned ch3:1;
	unsigned ch4:1;
	unsigned ch5:1;
	unsigned unused:2;
};

union extendedRange {
	struct extendedRangeBits asBits;
	unsigned char asChar;
};

struct model {
	unsigned char saved;
	unsigned char id;
	unsigned char name[NAME_SIZE];
	short trim[4];
	union extendedRange extended_range;
	unsigned char output_map[TOTAL_OUTPUT_CHANNELS];
	struct mix mix[MAX_MIXES];
};

