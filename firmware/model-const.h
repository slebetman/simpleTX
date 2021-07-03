#define MODEL_SIZE 48
#define MAX_MODELS 5

#define NAME_OFFSET 0
#define TRIM_OFFSET 10
#define SCALE_OFFSET 14
#define OUTPUT_MAP_OFFSET 18
#define MIX_OFFSET  22

#define REVERSE_MASK 0x80

struct mix {
	unsigned char input;
	unsigned char output;
	signed char scale;
	signed char expo;
	unsigned char reverse; // true/false
};

struct model {
	unsigned char name[10];
	unsigned int trim[4];
	unsigned int scale[4];
	unsigned char output_map[8];
	struct mix mix[8];
};

