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

#include "game.h"



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

void game(){
	
	init_hero();
	
	while(hero.lives != 0){
		run_engine();
	}
}

