const unsigned char smallFont[95*5] = {
	0x00, 0x00, 0x00, 0xff, 0x00, // space
	0xe8, 0xff, 0x00, 0x00, 0x00, // !
	0xc0, 0x00, 0xc0, 0xff, 0x00, // "
	0x00, 0x00, 0x00, 0x00, 0x00, // #
	0x00, 0x00, 0x00, 0x00, 0x00, // $
	0x00, 0x00, 0x00, 0x00, 0x00, // %
	0x00, 0x00, 0x00, 0x00, 0x00, // &
	0x00, 0x00, 0x00, 0x00, 0x00, // '
	0x00, 0x00, 0x00, 0x00, 0x00, // (
	0x00, 0x00, 0x00, 0x00, 0x00, // )
	0x00, 0x00, 0x00, 0x00, 0x00, // *
	0x00, 0x00, 0x00, 0x00, 0x00, // +
	0x08, 0x10, 0xff, 0x00, 0x00, // ,
	0x20, 0x20, 0x20, 0xff, 0x00, // -
	0x08, 0xff, 0x00, 0x00, 0x00, // .
	0x00, 0x00, 0x00, 0x00, 0x00, // /
	
	0x70, 0x88, 0x70, 0xff, 0x00, // 0
	0x88, 0xf8, 0x08, 0xff, 0x00, // 1
	0x98, 0xa8, 0x48, 0xff, 0x00, // 2
	0xa8, 0xa8, 0x50, 0xff, 0x00, // 3
	0xe0, 0x20, 0xf8, 0xff, 0x00, // 4
	0xe8, 0xa8, 0x90, 0xff, 0x00, // 5
	0x70, 0xa8, 0x10, 0xff, 0x00, // 6
	0x98, 0xa0, 0xc0, 0xff, 0x00, // 7
	0x50, 0xa8, 0x50, 0xff, 0x00, // 8
	0x40, 0xa8, 0x70, 0xff, 0x00, // 9
	
	0x00, 0x00, 0x00, 0x00, 0x00, // :
	0x00, 0x00, 0x00, 0x00, 0x00, // ;
	0x00, 0x00, 0x00, 0x00, 0x00, // <
	0x00, 0x00, 0x00, 0x00, 0x00, // =
	0x00, 0x00, 0x00, 0x00, 0x00, // >
	0x00, 0x00, 0x00, 0x00, 0x00, // ?
	0x00, 0x00, 0x00, 0x00, 0x00, // @
	
	0x78, 0xa0, 0xf8, 0xff, 0x00, // A
	0xf8, 0xa8, 0x50, 0xff, 0x00, // B
	0x70, 0x88, 0x88, 0xff, 0x00, // C
	0xf8, 0x88, 0x70, 0xff, 0x00, // D
	0xf8, 0xa8, 0x88, 0xff, 0x00, // E
	0xf8, 0xa0, 0x80, 0xff, 0x00, // F
	0x70, 0x88, 0xb8, 0xff, 0x00, // G
	0xf8, 0x20, 0xf8, 0xff, 0x00, // H
	0xf8, 0xff, 0x00, 0x00, 0x00, // I
	0x10, 0x08, 0xf0, 0xff, 0x00, // J
	0xf8, 0x20, 0x50, 0x88, 0xff, // K
	0xf8, 0x08, 0xff, 0x00, 0x00, // L
	0xf8, 0x40, 0x20, 0x40, 0xf8, // M
	0xf8, 0x40, 0x20, 0xf8, 0xff, // N
	0x70, 0x88, 0x88, 0x70, 0xff, // O
	0xf8, 0xa0, 0x40, 0xff, 0x00, // P
	0x70, 0x88, 0x90, 0x78, 0xff, // Q
	0xf8, 0xa0, 0x58, 0xff, 0x00, // R
	0x48, 0xa8, 0x90, 0xff, 0x00, // S
	0x80, 0xf8, 0x80, 0xff, 0x00, // T
	0xf8, 0x08, 0xf8, 0xff, 0x00, // U
	0xf8, 0x10, 0x20, 0xc0, 0xff, // V
	0xf8, 0x10, 0x20, 0x10, 0xf8, // W
	0xd8, 0x20, 0xd8, 0xff, 0x00, // X
	0xc8, 0x28, 0xf0, 0xff, 0x00, // Y
	0x98, 0xa8, 0xc8, 0xff, 0x00, // Z
	
	0x00, 0x00, 0x00, 0x00, 0x00, // [
	0x00, 0x00, 0x00, 0x00, 0x00, // \
	0x00, 0x00, 0x00, 0x00, 0x00, // ]
	0x00, 0x00, 0x00, 0x00, 0x00, // ^
	0x00, 0x00, 0x00, 0x00, 0x00, // _
	0x00, 0x00, 0x00, 0x00, 0x00, // `
	
	0x58, 0x68, 0x38, 0xff, 0x00, // a
	0xf8, 0x28, 0x10, 0xff, 0x00, // b
	0x10, 0x28, 0x28, 0xff, 0x00, // c
	0x10, 0x28, 0xf8, 0xff, 0x00, // d
	0x38, 0x58, 0x68, 0xff, 0x00, // e
	0x20, 0x78, 0xa0, 0xff, 0x00, // f
	0x24, 0x54, 0x78, 0xff, 0x00, // g
	0xf8, 0x20, 0x18, 0xff, 0x00, // h
	0xb8, 0xff, 0x00, 0x00, 0x00, // i
	0x08, 0x04, 0xb8, 0xff, 0x00, // j
	0xf8, 0x10, 0x28, 0xff, 0x00, // k
	0xf8, 0xff, 0x00, 0x00, 0x00, // l
	0x38, 0x20, 0x10, 0x20, 0x38, // m
	0x38, 0x20, 0x20, 0x18, 0xff, // n
	0x38, 0x28, 0x38, 0xff, 0x00, // o
	0x7c, 0x28, 0x10, 0xff, 0x00, // p
	0x10, 0x28, 0x7c, 0xff, 0x00, // q
	0x38, 0x20, 0xff, 0x00, 0x00, // r
	0x68, 0x58, 0xff, 0x00, 0x00, // s
	0x20, 0xf8, 0x20, 0xff, 0x00, // t
	0x38, 0x08, 0x38, 0xff, 0x00, // u
	0x38, 0x10, 0x20, 0xff, 0x00, // v
	0x38, 0x10, 0x20, 0x10, 0x38, // w
	0x28, 0x10, 0x28, 0xff, 0x00, // x
	0x24, 0x14, 0x38, 0xff, 0x00, // y
	0x58, 0x68, 0xff, 0x00, 0x00, // z
	
	0x00, 0x00, 0x00, 0x00, 0x00, // {
	0x00, 0x00, 0x00, 0x00, 0x00, // |
	0x00, 0x00, 0x00, 0x00, 0x00, // }
	0x00, 0x00, 0x00, 0x00, 0x00  // ~
};

