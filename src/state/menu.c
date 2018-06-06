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
#include "menu.h"
#include "video/video.h"

void menu(){

	video_resetScreenPtr();
	draw_menu();

	while (1){
		cpct_scanKeyboard();
		if(cpct_isKeyPressed(Key_1)){
			break;
		
		}else if(cpct_isKeyPressed(Key_2)){

			reasign_buttons();
			//video_switchBuffers();

			draw_menu();
			//video_switchBuffers();
		
		}else if(cpct_isKeyPressed(Key_3)){

			show_credits();
			//video_switchBuffers();

			draw_menu();
			//video_switchBuffers();

			while (cpct_isAnyKeyPressed()){
				cpct_scanKeyboard();
			};

		}
	}
}

void draw_menu(){

	u8* pvmem;

	cpct_drawSolidBox(CPCT_VMEM_START, 240, 64, 200);
	cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, 64, 0), 240, 16, 200);
	cpct_drawSolidBox(HW_BACKBUFFER, 240, 64, 200);
	cpct_drawSolidBox(cpct_getScreenPtr(HW_BACKBUFFER, 64, 0), 240, 16, 200);
	


	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 18, 20);
	cpct_drawStringM0("Welcome to", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);
	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 18, 35);
	cpct_drawStringM0("UnderWorld", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);	
	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 5, 75);
	cpct_drawStringM0("Press: ", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);
	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 5, 100);
	cpct_drawStringM0("1:To play", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);
	pvmem += 0x50 + 0x50;
	cpct_drawStringM0("2:Reasign buttons", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);
	pvmem += 0x50 + 0x50;
	cpct_drawStringM0("3:Credits", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);	
}

void reasign_buttons(){

	u8* pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 35, 100);

	cpct_drawSolidBox(CPCT_VMEM_START, 240, 64, 200);
	cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, 64, 0), 240, 16, 200);
	cpct_drawSolidBox(HW_BACKBUFFER, 240, 64, 200);
	cpct_drawSolidBox(cpct_getScreenPtr(HW_BACKBUFFER, 64, 0), 240, 16, 200);
	//video_clearScreen();

	cpct_drawStringM0("Up!", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);
	waitReleaseKey(Key_2);
	keys.up = waitAKey();
	waitReleaseKey(keys.up);

	cpct_drawStringM0("Down!", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);
	keys.down = waitAKey(); 
	waitReleaseKey(keys.down);

	cpct_drawStringM0("Left!", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);
	keys.left = waitAKey(); 
	waitReleaseKey(keys.left);

	cpct_drawStringM0("Right!", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);
	keys.right = waitAKey(); 
	waitReleaseKey(keys.right);
	
	cpct_drawStringM0("Shot! ", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);
	keys.shot = waitAKey(); 
	waitReleaseKey(keys.shot);
	
	cpct_drawStringM0("Menu!", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);
	keys.menu = waitAKey(); 
	waitReleaseKey(keys.menu);

	//cpct_clearScreen_f64(0);
}

void show_credits(){

	u8* pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 12, 60);
	
	cpct_drawSolidBox(CPCT_VMEM_START, 240, 64, 200);
	cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, 64, 0), 240, 16, 200);
	cpct_drawSolidBox(HW_BACKBUFFER, 240, 64, 200);
	cpct_drawSolidBox(cpct_getScreenPtr(HW_BACKBUFFER, 64, 0), 240, 16, 200);
	//video_clearScreen();

	cpct_drawStringM0("Robert Esclapez", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);
	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 38, 80);
	cpct_drawStringM0("&", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);
	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 15, 100);
	cpct_drawStringM0("Jesus Perales", pvmem, MENU_FOREGROUND_COLOR, MENU_BACKGROUND_COLOR);

	waitReleaseKey(Key_3);

	waitAKey();
	//cpct_clearScreen_f64(0);
}