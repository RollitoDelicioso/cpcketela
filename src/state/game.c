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

u16 offset = 0;  	// Offset in tiles of the start of the view window in the g_building tilemap
u8 scroll_x = 0, scroll_y = 0;
u8 screen_x = 0, screen_y = 0;

void update_all(){
	update_hero();
	update_bullets();
	update_enemies();
}

void draw_all(){
	// DRAW THE g_building TILEMAP SCROLLED
	//    Scroll is controlled by offset, which is just representing the index of the first
	// tile inside the g_building tilemap that has to be drawn.
	u8* vmem = video_getBackBufferPtr() + VIEWPORT_OFFSET;

	cpct_etm_drawTilemap4x8_ag(vmem, g_building + offset);

	draw_enemies();
	draw_hero();
	draw_bullets();
}

void run_engine(){

	update_all();
	draw_all();

	// After drawing the tilemap, switch video buffers to display recently drawn backbuffer
	video_switchBuffers();
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
   //cpct_disableFirmware();          // We use own mode and colours, firmware must be disabled
   //cpct_setVideoMode(0);            // Set video mode 0 (160x200 pixels, 20x25 characters, 16 colours)
   //cpct_setPalette(g_palette, 13);  // Set our own colours defined en g_palette (automatically generated in maps/tileset.c)
   //cpct_setBorder(HW_BLUE);         // Set border same as background colour: BLUE

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

void game(){

	init_hero();
	initialize();

    map_load((u8*) &maps_000);

	while (hero.lives != 0){

		run_engine();
		// Draw the viewport scrolled inside the g_building tilemap 
		// up to the current movement offset
		//drawBuidlingScrolled(offset);
	}
}

