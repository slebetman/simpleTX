const unsigned char smallFont[95*5] = {
	0x00, 0x00, 0x00, 0xff, 0x00, // space
	
	0x5f, // .#.# ####
	0xff, //
	0xff, //
	0xff, //
	0xff, // !
	
	0x07, // .... .###
	0x00, // .... ....
	0x07, // .... .###
	0xff, //
	0xff, // "
	
	0x14, // ...# .#..
	0x7f, // .### ####
	0x14, // ...# .#..
	0x7f, // .### ####
	0x14, // ...# .#..
	
	0x34, // ..#. .#..
	0xfe, // ..#. #.#.
	0x54, // .### ####
	0xfe, // ..#. #.#.
	0x58, // ...# ..#.
	
	0x23, // ..#. ..##
	0x10, // ...# ....
	0x08, // .... #...
	0x64, // .##. .#..
	0xff, //
	
	0x36, // ..## .##.
	0x49, // .#.. #..#
	0x55, // .#.# .#.#
	0x22, // ..#. ..#.
	0x50, // .#.# ....
	
	0x07, // .... .###
	0xff, //
	0xff, //
	0xff, //
	0xff, // '
	
	0x3e, // ..## ###.
	0x41, // .#.. ...#
	0xff, //
	0xff, //
	0xff, // (

	0x41, // .#.. ...#	
	0x3e, // ..## ###.
	0xff, 
	0xff, 
	0xff, // )
	
	0x22, // ..#. ..#.
	0x14, // ...# .#..
	0x7f, // .### ####
	0x14, // ...# .#..
	0x22, // ..#. ..#.
	
	0x08, // .... #...
	0x08, // .... #...
	0x3e, // ..## ###.
	0x08, // .... #...
	0x08, // .... #...
	
	0x40, // .#......
	0x30, // ..##....
	0xff, //
	0xff, //
	0xff, //
	
	0x08, // ....#...
	0x08, // ....#...
	0x08, // ....#...
	0x08, // ....#...
	0xff, //
	
	0x40, // .#......
	0xff, //
	0xff, //
	0xff, //
	0xff, //
	
	0xc0, // ##......
	0x30, // ..##....
	0x0c, // ....##..
	0x03, // ......##
	0xff, //
	
	0x3e, // ..## ###.
	0x41, // .#.. ...#
	0x41, // .#.. ...#
	0x3e, // ..## ###.
	0xff, //
	
	0x00, // .... ....
	0x42, // .#.. ..#.
	0x7f, // .### ####
	0x40, // .#.. ....
	0xff, //
	
	0x66, // .##. .##.
	0x51, // .#.# ...#
	0x49, // .#.. #..#
	0x46, // .#.. .##.
	0xff, //
	
	0x22, // ..#. ..#.
	0x49, // .#.. #..#
	0x49, // .#.. #..#
	0x36, // ..## .##.
	0xff, //
	
	0x1f, // ...# ####
	0x10, // ...# ....
	0x7f, // .### ####
	0x10, // ...# ....
	0xff, //
	
	0x4f, // .#.. ####
	0x49, // .#.. #..#
	0x49, // .#.. #..#
	0x31, // ..## ...#
	0xff, //
	
	0x3e, // ..## ###.
	0x49, // .#.. #..#
	0x49, // .#.. #..#
	0x32, // ..## ..#.
	0xff, //
	
	0x01, // .... ...#
	0x61, // .##. ...#
	0x19, // ...# #..#
	0x07, // .... .###
	0xff, //

	0x36, // ..## .##.
	0x49, // .#.. #..#
	0x49, // .#.. #..#
	0x36, // ..## .##.
	0xff, //

	0x06, // .... .##.
	0x49, // .#.. #..#
	0x29, // ..#. #..#
	0x1e, // ...# ###.
	0xff, //
	
	0x22, // ..#. ..#.
	0xff, //
	0xff, //
	0xff, //
	0xff, //

	0x40, // .#.. ....	
	0x32, // ..## ..#.
	0xff, //
	0xff, //
	0xff, //

	0x08, // .... #...
	0x14, // ...# .#..
	0x22, // ..#. ..#.
	0x41, // .#.. ...#
	0xff, //
	
	0x24, // ..#. .#..
	0x24, // ..#. .#..
	0x24, // ..#. .#..
	0x24, // ..#. .#..
	0xff, //
	
	0x41, // .#.. ...#
	0x22, // ..#. ..#.
	0x14, // ...# .#..
	0x08, // .... #...
	0xff, //

	0x02, // .... ..#.	
	0x59, // .#.# #..#
	0x06, // .... .##.
	0xff, //	
	0xff, //
	
	0x00, // ..## ###.
	0x00, // .#.. ...#
	0x00, // .#.# #..#
	0x00, // .#.# .#.#
	0x00, // .... ###.
	
	0x7e, // .### ###.
	0x11, // ...# ...#
	0x7e, // .### ###.
	0xff, //
	0xff, //
	
	0x7f, // .### ####
	0x49, // .#.. #..#
	0x36, // ..## .##.
	0xff, //
	0xff, //
	
	0x3e, // ..## ###.
	0x41, // .#.. ...#
	0x22, // ..#. ..#.
	0xff, //
	0xff, //
	
	0x7f, // .### ####
	0x41, // .#.. ...#
	0x3e, // ..## ###.
	0xff, //
	0xff, //
	
	0x7f, // .### ####
	0x49, // .#.. #..#
	0x41, // .#.. ...#
	0xff, //
	0xff, //
	
	0x7e, // .### ####
	0x09, // .... #..#
	0x01, // .... ...#
	0xff, //
	0xff, //
	
	0x3e, // ..## ###.
	0x41, // .#.. ...#
	0x29, // ..#. #..#
	0x7a, // .### #.#.
	0xff, //
	
	0x7f, // .### ####
	0x08, // .... #...
	0x08, // .... #...
	0x7f, // .### ####
	0xff, //
	
	0x41, // .#.. ...#
	0x7f, // .### ####
	0x41, // .#.. ...#
	0xff, //
	0xff, //
	
	0x30, // ..## ....
	0x40, // .#.. ....
	0x3f, // ..## ####
	0xff, //
	0xff, //
	
	0x7f, // .### ####
	0x0c, // .... ##..
	0x12, // ...# ..#.
	0x61, // .##. ...#
	0xff, //
	
	0x7f, // .### ####
	0x40, // .#.. ....
	0x40, // .#.. ....
	0xff, //
	0xff, //
	
	0x7f, // .### ####
	0x02, // .... ..#.
	0x0c, // .... ##..
	0x02, // .... ..#.
	0x7f, // .### ####
	
	0x7f, // .### ####
	0x04, // .... .#..
	0x08, // .... #...
	0x7f, // .### ####
	0xff, //
	
	0x3e, // ..## ###.
	0x41, // .#.. ...#
	0x41, // .#.. ...#
	0x3e, // ..## ###.
	0xff, //

	0x7f, // .### ####
	0x11, // ...# ...#
	0x0e, // .... ###.
	0xff, //
	0xff, //

	0x3e, // ..## ###.
	0x41, // .#.. ...#
	0x51, // .#.# ...#
	0x3e, // ..## ###.
	0x40, // .#.. ....	
	
	0x7f, // .### ####
	0x11, // ...# ...#
	0x6e, // .##. ###.
	0xff, //
	0xff, //
	
	0x26, // ..#. .##.
	0x49, // .#.. #..#
	0x49, // .#.. #..#
	0x32, // ..## ..#.
	0xff, //
	
	0x01, // .... ...#
	0x7f, // .### ####
	0x01, // .... ...#
	0xff, //
	0xff, //
	
	0x3f, // ..## ####
	0x40, // .#.. ....
	0x40, // .#.. ....
	0x3f, // ..## ####
	0xff, //
	
	0x0f, // .... ####
	0x30, // ..## ....
	0x40, // .#.. ....
	0x30, // ..## ....
	0x0f, // .... ####
	
	0x7f, // .### ####
	0x20, // ..#. ....
	0x18, // ...# #...
	0x20, // ..#. ....
	0x7f, // .### ####
	
	0x63, // .##. ..##
	0x14, // ...# .#..
	0x08, // .... #...
	0x14, // ...# .#..
	0x63, // .##. ..##

	0x03, // .... ..##
	0x04, // .... .#..
	0x78, // .### #...
	0x04, // .... .#..
	0x03, // .... ..##
	
	0x61, // .##. ...#
	0x51, // .#.# ...#
	0x49, // .#.. #..#
	0x45, // .#.. .#.#
	0x43, // .#.. ..##
	
	0x7f, // .### #### 
	0x41, // .#.. ...#
	0x41, // .#.. ...#
	0xff, //
	0xff, // [
	
	0x03, // .... ..##
	0x0c, // .... ##..
	0x30, // ..## ....
	0xc0, // ##.. ....
	0xff, //

	0x41, // .#.. ...#
	0x41, // .#.. ...#
	0x7f, // .### #### 
	0xff, //
	0xff, // ]
	
	0x04, // .... .#..
	0x02, // .... ..#.
	0x01, // .... ...#
	0x02, // .... ..#.
	0x04, // .... .#..
	
	0x40, // .#.. ....
	0x40, // .#.. ....
	0x40, // .#.. ....
	0x40, // .#.. ....
	0xff, // _
	
	0x04, // .... .#..
	0x03, // .... ..##
	0xff, //
	0xff, //
	0xff, // `

	0x30, // ..## ....
	0x4a, // .#.. #.#.
	0x2a, // ..#. #.#.
	0x7c, // .### ##..
	0xff, //
	
	0x7f, // .### ####
	0x48, // .#.. #...
	0x48, // .#.. #...
	0x30, // ..## ....
	0xff, //
	
	0x38, // ..## #...
	0x44, // .#.. .#..
	0x44, // .#.. .#..
	0x44, // .#.. .#..
	0xff, //
	
	0x30, // ..## ....
	0x48, // .#.. #...
	0x48, // .#.. #...
	0x7f, // .### ####
	0xff, //
	
	0x38, // ..## #...
	0x54, // .#.# .#..
	0x54, // .#.# .#..
	0x58, // .#.# #...
	0xff, //
	
	0x10, // ...# ....
	0x7f, // .### ###.
	0x10, // ...# ...#
	0x02, // .... ..#.
	0xff, //
	
	0x4c, // .#.. ##..
	0x92, // #..# ..#.
	0x7c, // .### ##..
	0xff, //
	0xff, //
	
	0x7f, // .### ####
	0x08, // .... #...
	0x70, // .### ....
	0xff, //
	0xff, //
	
	0x7a, // .### #.#.
	0xff, //
	0xff, //
	0xff, //
	0xff, //
	
	0x40, // .#.. ....
	0x80, // #... ....
	0x7a, // .### #.#.
	0xff, //
	0xff, //
	
	0x7f, // .### ####
	0x30, // ..## ....
	0x48, // .#.. #...
	0xff, //
	0xff, //
	
	0x7f, // .### ####
	0xff, //
	0xff, //
	0xff, //
	0xff, //
	
	0x7c, // .### ##..
	0x08, // .... #...
	0x70, // .### ....
	0x08, // .... #...
	0x70, // .### ....
	
	0x78, // .### #...
	0x08, // .... #...
	0x70, // .### ....
	0xff, //
	0xff, //
	
	0x38, // ..## #...
	0x44, // .#.. .#..
	0x44, // .#.. .#..
	0x38, // ..## #...
	0xff, //
	
	0xfc, // #### ##..
	0x24, // ..#. .#..
	0x18, // ...# #...
	0xff, //
	0xff, //
	
	0x18, // ...# #...
	0x24, // ..#. .#..
	0xfc, // #### ##..
	0xff, //
	0xff, //
	
	0x78, // .### #...
	0x04, // .... .#..
	0x04, // .... .#.. 
	0xff, //
	0xff, //
	
	0x44, // .#.. .#..
	0x4a, // .#.. #.#.
	0x32, // ..## ..#.
	0xff, //
	0xff, //
	
	0x08, // .... #...
	0x3f, // ..## ####
	0x48, // .#.. #...
	0xff, //
	0xff, //
	
	0x3c, // ..## ##..
	0x40, // .#.. ....
	0x40, // .#.. ....
	0x3c, // ..## ##..
	0xff, //
	
	0x3c, // ..## ##..
	0x40, // .#.. ....
	0x3c, // ..## ##..
	0xff, //
	0xff, //
	
	0x3c, // ..## ##..
	0x40, // .#.. ....
	0x30, // ..## ....
	0x40, // .#.. ....
	0x3c, // ..## ##..
	
	0x6c, // .##. ##..
	0x10, // ...# ....
	0x6c, // .##. ##..
	0xff, //
	0xff, //
	
	0x4c, // .#.. ##..
	0x90, // #..# ....
	0x7c, // .### ##..
	0xff, //
	0xff, //
	
	0x64, // .##. .#..
	0xa4, // .#.# .#..
	0x4c, // .#.. ##..
	0xff, //
	0xff, //
	
	0x00, 0x00, 0x00, 0x00, 0x00, // {
	0x00, 0x00, 0x00, 0x00, 0x00, // |
	0x00, 0x00, 0x00, 0x00, 0x00, // }
	0x00, 0x00, 0x00, 0x00, 0x00  // ~
};
