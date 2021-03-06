#include "tileset.h"
// Data created with Img2CPC - (c) Retroworks - 2007-2015
// Palette uses hardware values.
const u8 g_palette[16] = { 0x4d, 0x44, 0x5c, 0x58, 0x4c, 0x54, 0x56, 0x46, 0x57, 0x40, 0x4e, 0x47, 0x52, 0x53, 0x4a, 0x4b };

u8* const g_tileset[30] = { 
	g_tileset_00, g_tileset_01, g_tileset_02, g_tileset_03, g_tileset_04, g_tileset_05, g_tileset_06, g_tileset_07, g_tileset_08, g_tileset_09, g_tileset_10, g_tileset_11, g_tileset_12, g_tileset_13, g_tileset_14, g_tileset_15, g_tileset_16, g_tileset_17, g_tileset_18, g_tileset_19, g_tileset_20, g_tileset_21, g_tileset_22, g_tileset_23, g_tileset_24, g_tileset_25, g_tileset_26, g_tileset_27, g_tileset_28, g_tileset_29
};
// Tile g_tileset_00: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_00[4 * 8] = {
	0xc3, 0x96, 0x69, 0xc3,
	0xc3, 0xe1, 0xd2, 0xc3,
	0x69, 0xc3, 0xc3, 0x96,
	0xc3, 0xc3, 0xc3, 0xc3,
	0xc3, 0x69, 0xc3, 0xc3,
	0xc3, 0x69, 0xb4, 0xc3,
	0xc3, 0xc3, 0xc3, 0xe1,
	0x78, 0xc3, 0xc3, 0xe1
};

// Tile g_tileset_01: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_01[4 * 8] = {
	0xc3, 0x96, 0x69, 0xc3,
	0xc3, 0xe1, 0xd2, 0xc3,
	0x69, 0xc3, 0xc3, 0x96,
	0xc3, 0xc3, 0xc3, 0xc3,
	0xc3, 0x69, 0xc3, 0xc3,
	0xc3, 0x69, 0xb4, 0xc3,
	0xc3, 0xc3, 0xc3, 0xe1,
	0x78, 0xc3, 0xc3, 0xe1
};

// Tile g_tileset_02: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_02[4 * 8] = {
	0xc3, 0xd2, 0xd2, 0xc3,
	0xc3, 0xe1, 0xc3, 0xc3,
	0xd2, 0xc3, 0xd2, 0xc3,
	0xf0, 0xc3, 0xc3, 0xe1,
	0xe1, 0xd2, 0xe1, 0xd2,
	0xc3, 0xd2, 0xd2, 0xc3,
	0xd2, 0xc3, 0xc3, 0xf0,
	0xc3, 0xd2, 0xc3, 0xd2
};

// Tile g_tileset_03: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_03[4 * 8] = {
	0xc3, 0xd2, 0xd2, 0xc3,
	0xc3, 0xe1, 0xc3, 0xc3,
	0xd2, 0xc3, 0xd2, 0xc3,
	0xf0, 0xc3, 0xc3, 0xe1,
	0xe1, 0xd2, 0xe1, 0xd2,
	0xc3, 0xd2, 0xd2, 0xc3,
	0xd2, 0xc3, 0xc3, 0xf0,
	0xc3, 0xd2, 0xc3, 0xd2
};

// Tile g_tileset_04: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_04[4 * 8] = {
	0xc3, 0xd2, 0xe1, 0xc3,
	0xc3, 0xd2, 0xe1, 0xc3,
	0xd2, 0xd2, 0xc3, 0xd2,
	0xe1, 0xc3, 0xe1, 0xc3,
	0xe1, 0xc3, 0xd2, 0xd2,
	0xf0, 0xf0, 0xf0, 0xf0,
	0xe1, 0xc3, 0xf0, 0xd2,
	0xd2, 0xe1, 0xc3, 0xe1
};

// Tile g_tileset_05: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_05[4 * 8] = {
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0x72, 0xb1, 0xc0,
	0xc0, 0x33, 0x33, 0xc0,
	0xc0, 0xf0, 0xf0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0x33, 0x33, 0xc0,
	0xc0, 0x91, 0x62, 0xc0
};

// Tile g_tileset_06: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_06[4 * 8] = {
	0xf0, 0xf0, 0xf0, 0xf0,
	0xf8, 0xfc, 0xf8, 0xf4,
	0xf4, 0xe0, 0xd0, 0xf0,
	0xf8, 0xf0, 0xf0, 0xf4,
	0xf4, 0xfc, 0xf4, 0xf8,
	0xf0, 0xf0, 0xf0, 0xf0,
	0xf4, 0xf0, 0xf0, 0xf8,
	0xf8, 0xd0, 0xe0, 0xf0
};

// Tile g_tileset_07: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_07[4 * 8] = {
	0x42, 0xc0, 0xc0, 0x03,
	0x81, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0x03, 0xc0, 0xc0, 0xc0,
	0x81, 0xc0, 0xc0, 0x03,
	0x42, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0
};

// Tile g_tileset_08: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_08[4 * 8] = {
	0x42, 0xc0, 0xc0, 0x03,
	0x81, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0x03, 0xc0, 0xc0, 0xc0,
	0x81, 0xc0, 0xc0, 0x03,
	0x42, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0
};

// Tile g_tileset_09: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_09[4 * 8] = {
	0xc3, 0x86, 0x49, 0xc3,
	0xc3, 0x86, 0x49, 0xc3,
	0x86, 0x86, 0xc3, 0x86,
	0x49, 0xc3, 0x49, 0xc3,
	0x49, 0xc3, 0x86, 0x86,
	0x0c, 0x0c, 0x0c, 0x0c,
	0x49, 0xc3, 0x0c, 0x86,
	0x86, 0x49, 0xc3, 0x49
};

// Tile g_tileset_10: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_10[4 * 8] = {
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0x72, 0xb1, 0xc0,
	0xc0, 0x33, 0x33, 0xc0,
	0xc0, 0xf0, 0xf0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0x33, 0x33, 0xc0,
	0xc0, 0x91, 0x62, 0xc0
};

// Tile g_tileset_11: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_11[4 * 8] = {
	0xf0, 0xf0, 0xf0, 0xf0,
	0xf0, 0xfa, 0xe1, 0xf0,
	0xe1, 0xf5, 0xd2, 0xd2,
	0xfa, 0xf0, 0xf0, 0xf5,
	0xf0, 0xf5, 0xd2, 0xf0,
	0xf0, 0xf0, 0xf0, 0xf0,
	0xf5, 0xf0, 0xf0, 0xfa,
	0xd2, 0xfa, 0xe1, 0xe1
};

// Tile g_tileset_12: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_12[4 * 8] = {
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0
};

// Tile g_tileset_13: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_13[4 * 8] = {
	0x03, 0x52, 0xa1, 0x03,
	0x03, 0xd2, 0xe1, 0x03,
	0x52, 0xd2, 0xc3, 0xd2,
	0xa1, 0xc3, 0xe1, 0x03,
	0xf0, 0xc3, 0xd2, 0xd2,
	0xf0, 0xf0, 0xf0, 0xf0,
	0xe1, 0xc3, 0xf0, 0xd2,
	0xd2, 0xe1, 0xc3, 0xe1
};

// Tile g_tileset_14: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_14[4 * 8] = {
	0xf0, 0xf0, 0xf0, 0xf0,
	0x58, 0x58, 0x0c, 0xa4,
	0xa4, 0xf5, 0x0c, 0x58,
	0xf0, 0x58, 0xf0, 0xa4,
	0xa4, 0xa4, 0x0c, 0x58,
	0xf0, 0xf0, 0xf0, 0xf0,
	0xf0, 0xa4, 0xf0, 0x58,
	0x58, 0xfa, 0x0c, 0xa4
};

// Tile g_tileset_15: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_15[4 * 8] = {
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03
};

// Tile g_tileset_16: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_16[4 * 8] = {
	0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff,
	0xeb, 0xc3, 0xc3, 0xd7,
	0xd7, 0xc3, 0xc3, 0xeb,
	0xeb, 0x44, 0x44, 0xd7,
	0xd7, 0x44, 0x44, 0xeb,
	0xeb, 0x00, 0x44, 0xd7,
	0xd7, 0x44, 0x00, 0xeb
};

// Tile g_tileset_17: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_17[4 * 8] = {
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0
};

// Tile g_tileset_18: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_18[4 * 8] = {
	0xf0, 0xf0, 0xf0, 0xf0,
	0xf0, 0xf0, 0xf0, 0xf0,
	0xf5, 0xef, 0xdb, 0xf2,
	0xf2, 0xdb, 0xef, 0xf5,
	0xa1, 0x70, 0xe4, 0x72,
	0x72, 0xe4, 0x70, 0xa1,
	0xa1, 0x3c, 0xc0, 0x72,
	0x72, 0xc0, 0x3c, 0xa1
};

// Tile g_tileset_19: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_19[4 * 8] = {
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c
};

// Tile g_tileset_20: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_20[4 * 8] = {
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03
};

// Tile g_tileset_21: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_21[4 * 8] = {
	0xeb, 0x44, 0xcc, 0xd7,
	0xd7, 0xcc, 0x44, 0xeb,
	0xeb, 0xc3, 0xc3, 0xd7,
	0xd7, 0xc3, 0xc3, 0xeb,
	0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff,
	0xee, 0xcc, 0xcc, 0xdd,
	0xdd, 0xcc, 0xcc, 0xee
};

// Tile g_tileset_22: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_22[4 * 8] = {
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf
};

// Tile g_tileset_23: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_23[4 * 8] = {
	0xa0, 0x70, 0xe4, 0x7a,
	0x7a, 0xe4, 0x70, 0xa0,
	0xa0, 0x0c, 0xfc, 0x7a,
	0x7a, 0x03, 0x0c, 0xa0,
	0xf0, 0xf0, 0xf0, 0xf0,
	0xf0, 0xf0, 0xf0, 0xf0,
	0xa5, 0x4b, 0x92, 0x70,
	0x70, 0x92, 0x4b, 0xa5
};

// Tile g_tileset_24: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_24[4 * 8] = {
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c,
	0x3c, 0x3c, 0x3c, 0x3c
};

// Tile g_tileset_25: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_25[4 * 8] = {
	0xf0, 0xf0, 0xf0, 0xf0,
	0xd2, 0xc3, 0xc3, 0xe1,
	0xe1, 0xfa, 0xf5, 0xd2,
	0xd2, 0xff, 0xff, 0xe1,
	0xe1, 0xc3, 0xc3, 0xd2,
	0xf0, 0xf0, 0xf0, 0xf0,
	0xe1, 0xff, 0xff, 0xd2,
	0xd2, 0xf5, 0xfa, 0xe1
};

// Tile g_tileset_26: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_26[4 * 8] = {
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f
};

// Tile g_tileset_27: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_27[4 * 8] = {
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf,
	0xcf, 0xcf, 0xcf, 0xcf
};

// Tile g_tileset_28: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_28[4 * 8] = {
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x3f
};

// Tile g_tileset_29: 8x8 pixels, 4x8 bytes.
const u8 g_tileset_29[4 * 8] = {
	0xf0, 0xf0, 0xf0, 0xf0,
	0xd0, 0xe8, 0x74, 0xb0,
	0xf4, 0xf8, 0xf4, 0xf8,
	0xd0, 0xe8, 0x74, 0xb0,
	0xe0, 0xd4, 0xb8, 0x70,
	0xf0, 0xf0, 0xf0, 0xf0,
	0xe0, 0xd4, 0xb8, 0x70,
	0xf8, 0xf4, 0xf8, 0xf4
};

