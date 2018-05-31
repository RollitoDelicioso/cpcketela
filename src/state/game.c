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
#include "maps/maps.h"

u8 x_offset = 0, y_offset = 0;

void update_all(){
	update_hero();
	update_bullets();
	update_enemies();
}

void draw_all(){
	draw_hero();
	draw_bullets();
	draw_objects();
	draw_enemies();
}

void run_engine(){
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

   // DRAW THE g_building TILEMAP SCROLLED
   //    Scroll is controlled by offset, which is just representing the index of the first
   // tile inside the g_building tilemap that has to be drawn. 
   cpct_etm_drawTilemap4x8_ag(vmem, g_building + offset);

   // After drawing the tilemap, switch video buffers to display recently drawn backbuffer
   video_switchBuffers();
}

void initialize() {
   // DRAW SCROLL FRAME ON BOTH SCREEN BUFFERS
   //   This frame will stay the same during all redraws, and hence we draw it
   // only once on both video buffers. After that, we will only redraw the scrolling
   // g_building viewport, that will be drawn inside the frame.
   video_initBuffers();    // Initialize screen video buffers
   // SET UP INTERNAL VALUES FOR DRAWTILEMAP4x8_AG function
   //    We will use this function later on for each redraw of the viewport. However, as
   // internal values will always be the same (same tileset, tilemap and viewport size), we 
   // set them only once here, and then we just call the drawing function each time we need it.
   cpct_etm_setDrawTilemap4x8_ag(VIEWPORT_W, VIEWPORT_H, g_building_W, g_tileset_00);

}

void gameOver(){
	cpct_clearScreen_f64(0);
}

void game(){

	u16 offset = 0;  // Offset in tiles of the start of the view window in the g_building tilemap
	u8 x = 0, y = 0;

	init_hero();
	//initialize();

    //map_load((u8*) &maps_000);

	while (hero.lives > 0){
		run_engine();
		// Draw the viewport scrolled inside the g_building tilemap 
		// up to the current movement offset
	/*	drawBuidlingScrolled(offset);


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
		if (cpct_isKeyPressed(Key_A) && x > 0)                         { --x; x_offset -= 8; --offset; }
		if (cpct_isKeyPressed(Key_D) && x < g_building_W - VIEWPORT_W) { ++x; x_offset += 8; ++offset; }
		if (cpct_isKeyPressed(Key_W) && y > 0)                         { --y; y_offset -= 8; offset -= g_building_W; }
		if (cpct_isKeyPressed(Key_S) && y < g_building_H - VIEWPORT_H) { ++y; y_offset += 8; offset += g_building_W; }	
	*/
	}
	gameOver();
}

