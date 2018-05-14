#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <cpctelera.h>
#include "../keyboard/keyboard.h"

typedef struct {
	u8 x;
	u8 y;
	u8 px;
	u8 py;
	u8 width;
	u8 height;
} THero;

typedef struct {
	u8 x;
	u8 y;
	u8 px;
	u8 py;
	u8 weight;
	u8 height;
} TEnemy;

// Member functions
void draw_hero(THero* hero);
void erase_hero(THero* hero);
void init_hero(THero* hero);
void update_hero(THero* hero);

extern THero hero;

#endif