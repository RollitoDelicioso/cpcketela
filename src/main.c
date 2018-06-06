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
#include "state/menu.h"
#include "state/game.h"
#include "keyboard/keyboard.h"
#include "video/video.h"
#include <tilemap/tileset.h>            // Automatically generated tileset arrays declarations
#include <tilemap/building.h>           // Automatically generated g_building tilemap declarations
#include <music/FrisBot.h>

u8 number_of_interruptions = 0;

void InterruptServiceRoutine(){

	//cpct_scanKeyboard_if();

    if (++number_of_interruptions == 6){

        //cpct_akp_musicPlay();
        number_of_interruptions = 0;
    }
}

void settings(){

	cpct_disableFirmware();
	cpct_setInterruptHandler(InterruptServiceRoutine);
	cpct_setVideoMode(0);
    cpct_setPalette(g_palette, 16);  // Set our own colours defined en g_palette (automatically generated in maps/tileset.c)
    cpct_setBorder(HW_BLUE);         // Set border same as background colour: BLUE
    //cpct_akp_musicInit(song_ingame);
}

void main(void){

    // This game needs 2 hardware screens for double buffer.
    // First buffer: 0x8000 - 0xBFFF
    // Second buffer: 0xC000 - 0xFFFF
    // Stack: 0x8000 (backwards)
    cpct_setStackLocation((void*) 0x8000);
    settings();
    initKeyboard();
    //video_initBuffers();    // Initialize screen video buffers

    while (1){
        menu();
        game();
    }
}
