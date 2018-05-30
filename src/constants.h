#define true 1
#define false 0
#define bool u8

#define HERO_WIDTH 1
#define HERO_HEIGHT 8

#define ENEMY_WIDTH 1
#define ENEMY_HEIGHT 1

#define BULLETS_WIDTH 1
#define BULLETS_HEIGHT 1

#define MAX_ENEMIES_SCREEN 10

#define MAX_BULLETS_HERO 5
#define MAX_BULLETS_ENEMY 3

// Pointer to the second hardware screen
#define HW_BACKBUFFER (u8*)(0x8000)

// USEFUL CONSTANTS AND PRECALCULATIONS
#define TILE_W             4         	// Width of a tile in bytes
#define TILE_H             8          	// Height of a tile in bytes
#define VIEWPORT_W        20          	// Width of the viewport in tiles
#define VIEWPORT_H        18          	// Height of the viewport in tiles
#define VIEW_X            (0 * TILE_W)	// X location of the viewport in bytes
#define VIEW_Y            (0 * TILE_H) 	// Y location of the viewport in bytes

// Pre-calculate the offset in bytes at which the viewport has to be drawn. This place will
// be the same in relative coordinates. For instance, standard video memory starts at 0xC000.
// If this viewport was to be drawn at 0xC120, 0x120 would be the offset. This offset would
// be the same if it was to be drawn at a hardware backbuffer starting at 0x8000, as it would 
// be drawn at 0x8120. To calculate only this offset, we use cpctm_screenPtr with 0 as 
// video memory pointer. The resulting calculation will contain only the offset, and that offset
// could then be added to the start pointer of any video memory buffer to be used.
// Remember that we use cpctm_screenPtr macro because all values are constant, and so is the result.
#define VIEWPORT_OFFSET (u16)(cpctm_screenPtr(0, VIEW_X, VIEW_Y))
