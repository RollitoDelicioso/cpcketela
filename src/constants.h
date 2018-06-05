#define true 1
#define false 0
#define bool u8
#define null 0xFF


// COLORS
#define MENU_FOREGROUND_COLOR 15
#define MENU_BACKGROUND_COLOR 0

#define SCORE_FOREGROUND_COLOR 4
#define SCORE_BACKGROUND_COLOR 0

#define HEALTH_FOREGROUND_COLOR 4
#define HEALTH_BACKGROUND_COLOR 0

#define HERO_WIDTH 4
#define HERO_HEIGHT 16

#define ENEMY_WIDTH 4
#define ENEMY_HEIGHT 16

#define BULLETS_WIDTH 2
#define BULLETS_HEIGHT 8

#define BULLETS_SPEED_X 4
#define BULLETS_SPEED_Y 8;

#define OBJECT_WIDTH 4
#define OBJECT_HEIGHT 16

#define MAX_ENEMIES_SCREEN 30
#define MAX_PORTALS_SCREEN 4
#define MAX_OBJECTS_SCREEN 2

#define MAX_BULLETS_HERO 2
#define MAX_BULLETS_ENEMY 3
#define MAX_NUMBER_OBJECTIVE_BULLETS 3

// Pointer to the second hardware screen
#define HW_BACKBUFFER (u8*)(0x8000)

// USEFUL CONSTANTS AND PRECALCULATIONS
#define TILE_W             4         	// Width of a tile in bytes
#define TILE_H             8          	// Height of a tile in bytes
#define TILE_WP            8         	// Width of a tile in pixels
#define TILE_HP            8          	// Height of a tile in pixels
#define VIEWPORT_W        20          	// Width of the viewport in tiles
#define VIEWPORT_H        18          	// Height of the viewport in tiles
#define VIEWPORT_WP       160			// Width of the viewport in pixels
#define VIEWPORT_WB		  80			// Width of the viewport in bytes
#define VIEWPORT_HP		  144			// Height of the viewport in pixels
#define VIEW_X            (0 * TILE_W)	// X location of the viewport in bytes
#define VIEW_Y            (0 * TILE_H) 	// Y location of the viewport in bytes

#define START_TILE_SCROLL_X             11
#define START_TILE_SCROLL_Y             9

#define END_TILE_SCROLL_X   	        20
#define END_TILE_SCROLL_Y	            21



#define INIT_LETTERS_SCORE_POSITION (u16*)(0xD5F4)
#define INIT_LETTERS_SCORE_POSITION_BACKBUFFER (u16*)(0x95F4)
#define INIT_NUMBERS_SCORE_POSITION (u16*)(0xFE44)
#define INIT_NUMBERS_SCORE_POSITION_BACKBUFFER (u16*)(0xBE44)

#define INIT_LETTERS_HEALTH_POSITION (u16*)(0xD60B)
#define INIT_LETTERS_HEALTH_POSITION_BACKBUFFER (u16*)(0x960B)
#define INIT_NUMBERS_HEALTH_POSITION (u16*)(0xFE61)
#define INIT_NUMBERS_HEALTH_POSITION_BACKBUFFER (u16*)(0xBE61)

#define HERO_START_X_RELATIVE 40
#define HERO_START_Y_RELATIVE 72

#define HERO_SPEED_X 4
#define HERO_SPEED_Y 8

#define ENEMY_SPEED_X 4
#define ENEMY_SPEED_Y 8

#define NUMBER_OF_PIXELS_PER_BYTE 2

#define PROVISIONAL_FLOOR_TILE_ID maps_000[0]
#define PROVISIONAL_OBSTACLE_TILE_ID maps_000[1]
#define PROVISIONAL_ENEMY_OCUPIED_TILE_ID maps_000[2]
#define PROVISIONAL_PORTAL_LOCAL 16
#define PROVISIONAL_PORTAL_END 18

// Needs 16 bytes 
#define OBSTACLE_CREATE_RECTANGLE(X1,Y1,X2,Y2) X1,Y1,X2,Y1,X2,Y1,X2,Y2,X1,Y2,X2,Y2,X1,Y1,X1,Y2,

// Pre-calculate the offset in bytes at which the viewport has to be drawn. This place will
// be the same in relative coordinates. For instance, standard video memory starts at 0xC000.
// If this viewport was to be drawn at 0xC120, 0x120 would be the offset. This offset would
// be the same if it was to be drawn at a hardware backbuffer starting at 0x8000, as it would 
// be drawn at 0x8120. To calculate only this offset, we use cpctm_screenPtr with 0 as 
// video memory pointer. The resulting calculation will contain only the offset, and that offset
// could then be added to the start pointer of any video memory buffer to be used.
// Remember that we use cpctm_screenPtr macro because all values are constant, and so is the result.
#define VIEWPORT_OFFSET (u16)(cpctm_screenPtr(0, VIEW_X, VIEW_Y))
