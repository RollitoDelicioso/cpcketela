//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of CPCtelera: An Amstrad CPC Game Engine
//  Copyright (C) 2018 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <cpctelera.h>
#include <types.h>
#include "game.h"
#include "video/video.h"
#include <tilemap/tileset.h>              // Automatically generated tileset arrays declarations
#include <tilemap/building.h>             // Automatically generated g_building tilemap declarations
//#include <maps/frame_updown.h>          // Automatically generated g_frame_ud tilemap declarations
//#include <maps/frame_leftright.h>       // Automatically generated g_frame_lr tilemap declarations
#include "maps/maps.h"



void erase_all(){
	erase_hero();
	erase_bullets();
	erase_enemies();
}

void update_all(){
	update_hero();
	update_bullets();
	update_enemies();
}

void draw_all(){

	draw_hero();
	draw_bullets();
	draw_enemies();
}

void run_engine(){
	erase_all();
	update_all();
	draw_all();
	cpct_waitVSYNC();
}

////////////////////////////////////////////////////////////////////////////////////
// DRAW BUILDING SCROLLED
//    This function draws the scrolling background inside the frame, which is a 
// building. The parameter offset controls the offset at which the viewport to 
// be drawn is located, inside the g_building tilemap. By changing offset, different
// viewports are drawn, and a scrolling effect can be performed.
//
void drawBuidlingScrolled(u16 offset){
   // vmem points to the place in present hardware backbuffer where the viewport
   // is to be drawn. This place is the same inside a given hardware backbuffer,
   // and hence we can have a pre-calculated VIEWPORT_OFFSET to directly add to
   // the start of the current hardware backbuffer in memory 
   //u8* vmem = video_getBackBufferPtr() + VIEWPORT_OFFSET;
   u8* vmem = video_getBackBufferPtr() + VIEWPORT_OFFSET;

   //u8* p_map = (u8*) &g_building;
   //p_map[4*20] = 12;
   
   // DRAW THE g_building TILEMAP SCROLLED
   //    Scroll is controlled by offset, which is just representing the index of the first
   // tile inside the g_building tilemap that has to be drawn. 
   cpct_etm_drawTilemap4x8_ag(vmem, g_building + offset);
   //cpct_etm_drawTilemap2x4_f(60, 23, vmem, g_building + (120*20));
   //cpct_etm_drawTileBox2x4(0, 0, 40, 42, 120, 0xC000, g_building); 

   // After drawing the tilemap, switch video buffers to display recently drawn backbuffer
   video_switchBuffers();
}

////////////////////////////////////////////////////////////////////////////////////
// DRAW SCROLL FRAME
//    Draws a frame around the scrolling viewport in the screen. This frame is 
// just static decoration. This frame is defined using 2 tilemaps: one for up/down
// parts of the frame, and the other for left/right parts.
//
/*void drawFrame() {
   u8* vmem;   // Temporal pointer to use for drawing at calculated locations in the current back buffer
   u8* vmem_buffer = video_getBackBufferPtr();  // Get present Hardware Back Buffer were we are going to draw

   // DRAW UP-DOWN PARTS OF THE FRAME
   //
   //    Up-Down parts of the frame share the same tilemap (g_frame_ud), so we 
   // set up internal values for drawTilemap4x8_ag once, and then use it twice.
   // All values for this tilemap are automatically generated at maps/frame_updown.c.
   // Tileset data is automatically generated at maps/tileset.c
   // Size: (Complete Frame Width x g_frame_ud_H) = (20 x 4 tiles)
   // tilemap_width: g_frame_ud_W (21 tiles)
   // tileset: g_tileset (starts in memory at g_tileset_00)
   cpct_etm_setDrawTilemap4x8_ag (20, 4, g_frame_ud_W, g_tileset_00);
   // Draw the upper part of the tilemap at the start of the hardware backbuffer
   cpct_etm_drawTilemap4x8_ag    (vmem_buffer, g_frame_ud);
   // Draw the lower part of the tilemap. First, calculate its location from coordinates:
   //   Coord.X: At the left part of the screen, so 0.
   //   Coord.Y: As this part of the frame is 4 tiles wide, and the complete frame takes 24
   //            tiles, this is to be located at tile 24-4 = 20.
   // Both coordinates need to be multiplied by width and height of tiles in bytes, to get
   // actual byte coordinates for getScreenPtr.
   vmem = cpct_getScreenPtr   (vmem_buffer,  0*TILE_W, 20*TILE_H);
   // This lower part will be displaced 1 tile to the right to create the effect of a 
   // displaced frame. The g_frame_ud tilemap is 21 tiles wide for this.
   cpct_etm_drawTilemap4x8_ag (vmem, g_frame_ud + 1);

   // DRAW LEFT-RIGHT PARTS OF THE FRAME
   //
   //    We follow same scheme as with Up-Down parts, but we use a different tilemap
   // (g_frame_lr) which is designed for this. This tilemap has both left and right 
   // frame parts integrated, so half the tilemap is the left part, and the other half 
   // the right part.
   // All values for this tilemap are automatically generated at maps/frame_leftright.c.
   // Size: (g_frame_lr_W/2 x g_frame_lr_H) = (2 x 16 tiles)
   // tilemap_width: g_frame_lr_W (4 tiles)
   // tileset: g_tileset (starts in memory at g_tileset_00)   
   cpct_etm_setDrawTilemap4x8_ag( 2, 16, g_frame_lr_W, g_tileset_00);
   // Draw the left part of the tilemap just below previously drawn upper part,
   // that is at (0, 4) tile coordinates.
   vmem = cpct_getScreenPtr   (vmem_buffer,  0*TILE_W, 4*TILE_H);
   cpct_etm_drawTilemap4x8_ag (vmem, g_frame_lr);   
   // Draw the right part of the tilemap just below previously drawn upper part, and at the
   // right-most part of the screen. At (20 - 2, 4) = (18, 4) tile coordinates.
   vmem = cpct_getScreenPtr   (vmem_buffer, 18*TILE_W, 4*TILE_H);
   cpct_etm_drawTilemap4x8_ag (vmem, g_frame_lr + 2);
}*/

void initialize() {
   //cpct_disableFirmware();          // We use own mode and colours, firmware must be disabled
   //cpct_setVideoMode(0);            // Set video mode 0 (160x200 pixels, 20x25 characters, 16 colours)
   //cpct_setPalette(g_palette, 13);  // Set our own colours defined en g_palette (automatically generated in maps/tileset.c)
   //cpct_setBorder(HW_BLUE);         // Set border same as background colour: BLUE

   // DRAW SCROLL FRAME ON BOTH SCREEN BUFFERS
   //   This frame will stay the same during all redraws, and hence we draw it
   // only once on both video buffers. After that, we will only redraw the scrolling
   // g_building viewport, that will be drawn inside the frame.
   video_initBuffers();    // Initialize screen video buffers
   //drawFrame();            // Draw a frame at the first selected screen buffer
   //video_switchBuffers();  // Switch video buffers (current screen <--> current backbuffer)
   //drawFrame();            // Draw the same frame at the second screen buffer

   // SET UP INTERNAL VALUES FOR DRAWTILEMAP4x8_AG function
   //    We will use this function later on for each redraw of the viewport. However, as
   // internal values will always be the same (same tileset, tilemap and viewport size), we 
   // set them only once here, and then we just call the drawing function each time we need it.
   cpct_etm_setDrawTilemap4x8_ag(VIEWPORT_W, VIEWPORT_H, g_building_W, g_tileset_00);
   //cpct_etm_setTileset2x4(g_tileset);

}

void game(){

	u16 offset = 0;  // Offset in tiles of the start of the view window in the g_building tilemap
   u8 x = 0, y = 0; // (x, y) coordinates of the start of the view window in the g_building tilemap
	
	//init_hero();
	initialize();
   //video_initBuffers();
   //cpct_etm_setTileset2x4(g_tileset);
   //video_initBuffers();
      
   //cpct_etm_setTileset2x4(g_tileset);
   //cpct_etm_drawTileBox2x4(0, 0, 40, 46, 120, CPCT_VMEM_START, g_building);
   map_load((u8*) &maps_000);

	while (hero.lives != 0){
		//run_engine();
		// Draw the viewport scrolled inside the g_building tilemap 
      // up to the current movement offset
      drawBuidlingScrolled(offset);
      //cpct_etm_drawTileBox2x4(0, 0, VIEWPORT_W, VIEWPORT_H, g_building_W, video_getBackBufferPtr() + VIEWPORT_OFFSET, g_building + offset);
      //video_switchBuffers();
      //cpct_etm_drawTilemap2x4(g_building_W, g_building_H, CPCT_VMEM_START, g_building + offset);

      //erase_herop(offset);
      //ee

      // Check user input and update offset accordingly (OPQA for movement)
      // Use (x, y) coordinates of the upper-left tile of the viewport to determine 
      // valid movements (those that maintain viewport inside g_building tilemap boundaries).
      // Size of the viewport (VIEWPORT_W, VIEWPORT_H) is used to check boundaries.
      // Offset value update:
      //    - Right-Left movements select previous-next tile in the tilemap, so offset requires 
      //      to be updated (-1 for left), (+1 for right).
      //    - Up-Down movements want to select one tile up or one tile down. However, as the tilemap
      //      is stored as a 2D-array, it means that one tile up or down is 1 row away in memory
      //      (Each row is stored in memory after the previous row). Therefore, to select up-down
      //      tiles in memory, offset requires to be updated (-g_building_W for up), (+g_building_W for down)
      //
      cpct_scanKeyboard_f();
      if (cpct_isKeyPressed(Key_A) && x > 0)                         { --x; --offset; }
      if (cpct_isKeyPressed(Key_D) && x < g_building_W - VIEWPORT_W) { ++x; ++offset; }
      if (cpct_isKeyPressed(Key_W) && y > 0)                         { --y; offset -= g_building_W; }
      if (cpct_isKeyPressed(Key_S) && y < g_building_H - VIEWPORT_H) { ++y; offset += g_building_W; }	
	}
}

