#include "channels.h"

#define NAME_SIZE          10
#define NAME_OFFSET        0
#define TRIM_OFFSET        (NAME_OFFSET+NAME_SIZE)
#define SCALE_OFFSET       (TRIM_OFFSET+2)
#define OUTPUT_MAP_OFFSET  (SCALE_OFFSET+3)
#define MIX_OFFSET         (OUTPUT_MAP_OFFSET+3)

#define MAX_MIXES   10
#define MIX_SIZE    3
#define MODEL_SIZE  (MIX_OFFSET+(MIX_SIZE*MAX_MIXES))
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
	unsigned char saved;
	unsigned char id;
	unsigned char name[NAME_SIZE];
	short trim[2];
	unsigned char scale[3];
	unsigned char output_map[TOTAL_OUTPUT_CHANNELS];
	struct mix mix[MAX_MIXES];
};

