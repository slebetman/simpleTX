#include "channels.h"

#define NAME_SIZE          10
#define NAME_OFFSET        0
#define TRIM_OFFSET        NAME_OFFSET+NAME_SIZE
#define SCALE_OFFSET       TRIM_OFFSET+4
#define OUTPUT_MAP_OFFSET  SCALE_OFFSET+4
#define MIX_OFFSET         OUTPUT_MAP_OFFSET+4

#define MAX_MIXES   10
#define MIX_SIZE    3
#define MODEL_SIZE  MIX_OFFSET+(MIX_SIZE*MAX_MIXES)
#define MAX_MODELS  5

#define REVERSE_MASK 0x80

struct mix {
	unsigned char input;
	unsigned char output;
	signed char scale;
	signed char expo;
	unsigned char reverse; // true/false
};

struct model {
	unsigned char name[NAME_SIZE];
	unsigned short trim[4];
	unsigned short scale[4];
	unsigned char output_map[TOTAL_OUTPUT_CHANNELS];
	struct mix mix[MAX_MIXES];
};

