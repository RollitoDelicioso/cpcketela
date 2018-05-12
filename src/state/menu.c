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

#include "menu.h"
#include "../keyboard/keyboard.h"

void initMenu(){
	u8* pvmem;  // Pointer to video memory
		
	// Pointer to memory, width, height   

	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 20, 20);
	cpct_drawStringM1("Welcome to CPCKetela!", pvmem, 1, 0);
	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 15, 55);
	cpct_drawStringM1("Press: ", pvmem, 1, 0);
	pvmem = cpct_getScreenPtr(CPCT_VMEM_START, 20, 70);
	cpct_drawStringM1("1: To play", pvmem, 1, 0);
	pvmem += 0x50 + 0x50;
	cpct_drawStringM1("2: Reasign buttons", pvmem, 1, 0);
	pvmem += 0x50 + 0x50;
	cpct_drawStringM1("3: Credits", pvmem, 1, 0);	

	while (1/*true*/){

		cpct_scanKeyboard_f();
		//cpct_scanKeyboard(); If memory is required uncomment this line, and comment the above one.
		if (cpct_isKeyPressed(Key_1)){
        	break;
    	}
	}
}