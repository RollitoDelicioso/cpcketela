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

#include "keyboard.h"

TKeys keys;

void initKeyboard(){
    keys.left = Key_A;
    keys.right = Key_D; 
    keys.up = Key_W;
    keys.down = Key_S;
    keys.menu = Key_P;
    keys.shot = Key_Space;
}

cpct_keyID waitAKey() {
    // Backwards bucle to get it finish in 0 (so the compiler will optimize it)
    u8 i = 10, *keys = cpct_keyboardStatusBuffer + 9;
    u16 keypressed;
    
    // Wait untile a key is pressed.
    do{
        cpct_scanKeyboard();
    }
    while ( ! cpct_isAnyKeyPressed() );
    
    // Key detection
    do {
        // if in this 8 keys group there is any key pressed, some of their bits will be 0.
        // else, all values will be 1, and a XOR with 0xFF returns 0 (FALSE).
        keypressed = *keys ^ 0xFF;
        if (keypressed)            
            return (keypressed << 8) + (i - 1);  // Format cpct_keyID: 8 first bits = key maks, the next 8 are the row in keyboard (0-9)
        keys--;
    } while(--i);
}
void waitReleaseKey(cpct_keyID key){
    while (cpct_isKeyPressed(key)){
        cpct_scanKeyboard();
    }
}