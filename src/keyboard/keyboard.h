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

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <cpctelera.h>


// Player Key Structure 
typedef struct {
  cpct_keyID up;
  cpct_keyID down;
  cpct_keyID left;
  cpct_keyID right;
  cpct_keyID shot;
  cpct_keyID menu;
} TKeys;

extern TKeys keys;

cpct_keyID waitAKey();
void initKeyboard();
void waitReleaseKey(cpct_keyID key);

#endif