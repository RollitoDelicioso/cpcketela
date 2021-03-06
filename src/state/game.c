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
#include "entity/entity.h"
#include <tilemap/tileset.h>              // Automatically generated tileset arrays declarations
#include <tilemap/map1.h>             // Automatically generated g_building tilemap declarations
#include "maps/maps.h"

u16 offset = 0;  	// Offset in tiles of the start of the view window in the g_building tilemap
u8 scroll_x = 0, scroll_y = 0;
u8 screen_x = 0, screen_y = 0;
u8 initialized = 0;
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

	draw_objects();
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
   //screen_y = scroll_y = screen_x = scroll_x = offset = 0;
	//cpct_drawStringM0("SCORE", INIT_LETTERS_SCORE_POSITION, SCORE_FOREGROUND_COLOR, SCORE_BACKGROUND_COLOR);
	//cpct_drawStringM0("SCORE", INIT_LETTERS_SCORE_POSITION_BACKBUFFER, SCORE_FOREGROUND_COLOR, SCORE_BACKGROUND_COLOR);
	
    cpct_drawSolidBox(CPCT_VMEM_START, 240, 64, 200);
	cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, 64, 0), 240, 16, 200);
	cpct_drawSolidBox(HW_BACKBUFFER, 240, 64, 200);
	cpct_drawSolidBox(cpct_getScreenPtr(HW_BACKBUFFER, 64, 0), 240, 16, 200);

	//cpct_drawStringM0("HEALTH", INIT_LETTERS_HEALTH_POSITION, HEALTH_FOREGROUND_COLOR, HEALTH_BACKGROUND_COLOR);
	//cpct_drawStringM0("HEALTH", INIT_LETTERS_HEALTH_POSITION_BACKBUFFER, HEALTH_FOREGROUND_COLOR, HEALTH_BACKGROUND_COLOR);
}


void youWin(){
	//cpct_clearScreen_f64(0);
	//video_clearScreen();
	u8* pvmem = 0;

	cpct_drawSolidBox(CPCT_VMEM_START, 240, 64, 200);
	cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, 64, 0), 240, 16, 200);
	cpct_drawSolidBox(HW_BACKBUFFER, 240, 64, 200);
	cpct_drawSolidBox(cpct_getScreenPtr(HW_BACKBUFFER, 64, 0), 240, 16, 200);


	pvmem = cpct_getScreenPtr(video_getBackBufferPtr(), 20, 85);
	cpct_drawStringM0("YOU   WIN", pvmem, GAME_OVER_FOREGROUND_COLOR, GAME_OVER_BACKGROUND_COLOR);

	pvmem = cpct_getScreenPtr(video_getBackBufferPtr(), 13, 105);
	cpct_drawStringM0("Press any key", pvmem, GAME_OVER_FOREGROUND_COLOR, GAME_OVER_BACKGROUND_COLOR);

	video_switchBuffers();


	while (cpct_isAnyKeyPressed_f()){
		cpct_scanKeyboard();
	}


	while (!cpct_isAnyKeyPressed_f()){
		cpct_scanKeyboard();
	}
}

void gameOver(){
	//cpct_clearScreen_f64(0);
	//video_clearScreen();
	u8* pvmem = 0;

	cpct_drawSolidBox(CPCT_VMEM_START, 240, 64, 200);
	cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, 64, 0), 240, 16, 200);
	cpct_drawSolidBox(HW_BACKBUFFER, 240, 64, 200);
	cpct_drawSolidBox(cpct_getScreenPtr(HW_BACKBUFFER, 64, 0), 240, 16, 200);


	pvmem = cpct_getScreenPtr(video_getBackBufferPtr(), 20, 85);
	cpct_drawStringM0("Game Over", pvmem, GAME_OVER_FOREGROUND_COLOR, GAME_OVER_BACKGROUND_COLOR);

	pvmem = cpct_getScreenPtr(video_getBackBufferPtr(), 13, 105);
	cpct_drawStringM0("Press any key", pvmem, GAME_OVER_FOREGROUND_COLOR, GAME_OVER_BACKGROUND_COLOR);

	video_switchBuffers();


	while (cpct_isAnyKeyPressed_f()){
		cpct_scanKeyboard();
	}


	while (!cpct_isAnyKeyPressed_f()){
		cpct_scanKeyboard();
	}
}

void preload(){
	map_load((u8*) &maps_001);
	print_score();
	print_health();
}

void game(){

	init_hero();
	if(initialized == 0){
		initialize();
		initialized = 1;
	}

	preload();

	while (hero.lives > 0 && hero.won != 1){
		run_engine();
	}

	if(hero.won == 1){
		youWin();
	}else{		
		gameOver();
	}
}

