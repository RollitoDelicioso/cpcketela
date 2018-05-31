#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <cpctelera.h>
#include "../keyboard/keyboard.h"
#include "../constants.h"

typedef struct {
	u8 x;
	u8 y;
	u8 ldf; // L.D.F (Last Direcction Faced) To know witch direction should face the bullet.
			// 0: up, 1: down, 2: left, 3: right, 4:up-left, 5:up-right, 6:down-left, 7:down-right
	i8 lives;
} THero;

typedef struct {
	u8 x;
	u8 y;
	void (*perform_action)(u8*);
	u8 ctpa; //count_to_perform_action
	u8 lives;
} TEnemy;

typedef struct {
	u8 x; // -1 Means that the bullet is not going to be processed"
	u8 y;
	u8 dir; // Direction of the bullet
		//0: right
} TBullet;

typedef struct {
	u8 x;
	u8 y;
	u8 picked; //0: no 1:yes
	void (*perform_action)(u8*);
} TObject;
// Member functions

// Hero
void update_hero();
void draw_hero();
void init_hero();
//Enemies
void update_enemies();
void draw_enemies();

//Bullets
void check_collisions();
void update_bullets();
void draw_bullets();
void shot(u8 who);
void fill_spot_bullet(TBullet* array_bullets);

//Objects
void draw_objects();

extern THero hero;
extern const TEnemy enemies[MAX_ENEMIES_SCREEN];
extern const TBullet bullet_hero;
extern const TBullet bullets_enemies[MAX_BULLETS_ENEMY];
extern const u8 n_hero_bullets_on_screen;
extern const u8 n_hero_enemy_on_screen;


#endif