#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <cpctelera.h>
#include "../keyboard/keyboard.h"
#include "../constants.h"

typedef struct {
	u8 x;
	u8 y;
	u8 px;	// Previous x
	u8 py;	// Previous y
	u8 ldf; // L.D.F (Last Direcction Faced) To know witch direction should face the bullet.
			// 0: up, 1: down, 2: left, 3: right, 4:up-left, 5:up-right, 6:down-left, 7:down-right
	u8 lives;
} THero;

typedef struct {
	u8 x;
	u8 y;
	u8 px;
	u8 py;
	u8 lives;
} TEnemy;

typedef struct {
	u8 x; // -1 Means it is not been "processed"
	u8 y;
	u8 direction; // Direction of the bullet
		//0: right
	u8 px;
	u8 py;
} TBullets;


// Member functions

void update_hero();
void erase_hero();
void draw_hero();
void init_hero();


void update_bullets();
void erase_bullets();
void draw_bullets();


void shot(u8 who);
void fill_spot(TBullets* array_bullets);

extern THero hero;
extern TEnemy enemies[MAX_ENEMIES_SCREEN];
extern const TBullets bullets_hero[MAX_BULLETS_HERO];
extern TBullets bullets_enemies[MAX_BULLETS_ENEMY];


#endif