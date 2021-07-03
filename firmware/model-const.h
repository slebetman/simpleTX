#define MODEL_SIZE 42
#define MAX_MODELS 6

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
	struct mix mix[8];
};

