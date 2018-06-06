#include "entity.h"
#include "state/game.h"
#include "video/video.h"
#include "maps/maps.h"

#include <cpctelera.h>
#include <tilemap/tileset.h>            // Automatically generated tileset arrays declarations
#include <tilemap/building.h>           // Automatically generated g_building tilemap declarations
#include <sprites/hero_frontal.h>
#include <sprites/hero_trasera.h>
#include <sprites/hero_lateral_izquierda.h>
#include <sprites/hero_lateral_derecha.h>
#include <sprites/hero_superior_izquierda.h>
#include <sprites/hero_superior_derecha.h>
#include <sprites/crab_frontal.h>
#include <sprites/crab_trasera.h>
#include <sprites/crab_izquierda.h>
#include <sprites/crab_derecha.h>
#include <sprites/crab_superior_izquierda.h>
#include <sprites/crab_superior_derecha.h>
#include <sprites/wizard_frontal.h>
#include <sprites/wizard_trasera.h>
#include <sprites/wizard_izquierda.h>
#include <sprites/wizard_derecha.h>
#include <sprites/wizard_superior_izquierda.h>
#include <sprites/wizard_superior_derecha.h>
#include <sprites/demon_frontal.h>
#include <sprites/demon_trasera.h>
#include <sprites/demon_lateral_izquierda.h>
#include <sprites/demon_lateral_derecha.h>
#include <sprites/demon_inferior_izquierda.h>
#include <sprites/demon_inferior_derecha.h>

#define INIT_BULLET {0xFF, 0, 0}
#define INIT_OBJECTIVE_BULLET {0xFF, 0, 0, 0, 0, 0x0000}
#define INIT_PORTAL {0xFF,0,0,0}
#define INIT_ENEMY {0,0,0,chase_hero,0,0,2, (u8*) &g_crab_izquierda}
#define MAX_NUMBER_OF_UPDATED_ENEMYS 10
#define START_ITERATION 0
#define END_ITERATION 30


THero hero;
const u8 s10k, s1k, s100, s10, s1;
const u8 h100, h10, h1;
const TEnemy enemies[MAX_ENEMIES_SCREEN] = {{4,8,0,chase_hero,15,1, 2, (u8*) &g_crab_izquierda}, INIT_ENEMY, INIT_ENEMY, INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY, INIT_ENEMY, INIT_ENEMY, INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY, INIT_ENEMY, INIT_ENEMY, INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY,INIT_ENEMY};
const TBullet bullet_hero = {0xFF,0,0};
const TBullet bullets_enemies[MAX_BULLETS_ENEMY] = {INIT_BULLET, INIT_BULLET, INIT_BULLET};
const TOBullet bullets_enemies_objective[MAX_BULLETS_ENEMY] = {INIT_OBJECTIVE_BULLET, INIT_OBJECTIVE_BULLET, INIT_OBJECTIVE_BULLET};
const TObject objects[MAX_OBJECTS_SCREEN] = {{20,20,0,add_score}, {10,100,0,increase_heal}};
const TPortal portals[MAX_PORTALS_SCREEN] = {INIT_PORTAL,INIT_PORTAL,INIT_PORTAL,INIT_PORTAL};
const TPortalNextMap;
const u8 n_hero_bullets_on_screen = 0;
const u8 n_enemy_bullets_on_screen = 0;
const u8 n_enemy_objective_bullets_on_screen = 0;
u8 current_iteration = 0;
const u8* current_map;
u8 current_index = 0;

const u8 bullet_table_x[8] = {
	HERO_WIDTH/2 - BULLETS_WIDTH/2, 	//up
	HERO_WIDTH/2 - BULLETS_WIDTH/2, 	//down
	BULLETS_WIDTH, //left
	0, 	//right
	BULLETS_WIDTH, //up-left
	0,		//up-right
	BULLETS_WIDTH,	//down-left
	0		//up-right
};
const u8 bullet_table_y[8] = {
	0,	//up
	HERO_HEIGHT/2,		//down
	HERO_HEIGHT/2 - BULLETS_HEIGHT/2,		//left
	HERO_HEIGHT/2 - BULLETS_HEIGHT/2,		//right
	0,	//up-left
	0, 	//up-right
	HERO_HEIGHT/2,		//down-left
	HERO_HEIGHT/2 		//down-right
};

void calculate_new_score(){
	u8* p = &s10k;
	u16* hero_score = &hero.score;

	(*p) = (*hero_score)/10000;
	p++;
	(*p) = ((*hero_score)%10000)/1000;
	p++;
	(*p) = ((*hero_score)%1000)/100;
	p++;
	(*p) = ((*hero_score)%100)/10;
	p++;
	(*p) = (*hero_score)%10;
}

void print_score_aux(u16* mem){

	cpct_drawStringM0("SCORE", INIT_LETTERS_SCORE_POSITION, SCORE_FOREGROUND_COLOR, SCORE_BACKGROUND_COLOR);
	cpct_drawStringM0("SCORE", INIT_LETTERS_SCORE_POSITION_BACKBUFFER, SCORE_FOREGROUND_COLOR, SCORE_BACKGROUND_COLOR);

	cpct_drawCharM0(mem,SCORE_FOREGROUND_COLOR,SCORE_BACKGROUND_COLOR,s10k+48);
	mem += 2;  
	cpct_drawCharM0(mem,SCORE_FOREGROUND_COLOR,SCORE_BACKGROUND_COLOR,s1k+48);
	mem += 2;  
	cpct_drawCharM0(mem,SCORE_FOREGROUND_COLOR,SCORE_BACKGROUND_COLOR,s100+48);
	mem += 2;  
	cpct_drawCharM0(mem,SCORE_FOREGROUND_COLOR,SCORE_BACKGROUND_COLOR,s10+48);
	mem += 2;  
	cpct_drawCharM0(mem,SCORE_FOREGROUND_COLOR,SCORE_BACKGROUND_COLOR,s1+48);
}

void print_score(){
	calculate_new_score();
	print_score_aux(INIT_NUMBERS_SCORE_POSITION);
	print_score_aux(INIT_NUMBERS_SCORE_POSITION_BACKBUFFER);
}

void calculate_new_health(){
	u8* p = &h100;
	i8* hero_lives = &hero.lives;

	(*p) = (*hero_lives)/100;
	p++;
	(*p) = ((*hero_lives)%100)/10;
	p++;
	(*p) = (*hero_lives)%10;
}

void print_health_aux(u16* mem){

	cpct_drawStringM0("HEALTH", INIT_LETTERS_HEALTH_POSITION, HEALTH_FOREGROUND_COLOR, HEALTH_BACKGROUND_COLOR);
	cpct_drawStringM0("HEALTH", INIT_LETTERS_HEALTH_POSITION_BACKBUFFER, HEALTH_FOREGROUND_COLOR, HEALTH_BACKGROUND_COLOR);

	cpct_drawCharM0(mem,HEALTH_FOREGROUND_COLOR,HEALTH_BACKGROUND_COLOR,h100+48); 
	mem += 2;  
	cpct_drawCharM0(mem,HEALTH_FOREGROUND_COLOR,HEALTH_BACKGROUND_COLOR,h10+48); 
	mem += 2;  
	cpct_drawCharM0(mem,HEALTH_FOREGROUND_COLOR,HEALTH_BACKGROUND_COLOR,h1+48); 
}

void print_health(){
	calculate_new_health();
	print_health_aux(INIT_NUMBERS_HEALTH_POSITION);
	print_health_aux(INIT_NUMBERS_HEALTH_POSITION_BACKBUFFER);
}

void add_score(u8* picked){
	u8* p = picked;
	(*p)++;
	hero.score += 100;
	print_score();
}

void shot_objective(u8* enemy){		// Demon loquillo
	
	bool left = false, right = false;
	u8* p = enemy;
	TEnemy* ptr_enemy = (TEnemy*) enemy;

	// Check left
	if (hero.x < (*p)){

		ptr_enemy->ldf = 2;
		ptr_enemy->sprite = (u8*) &g_demon_lateral_izquierda;
		left = true;
	}
	// Check right
	else {

		ptr_enemy->ldf = 3;
		ptr_enemy->sprite = (u8*) &g_demon_lateral_derecha;
		right = true;
	}

	p++;

	// Check up
	if (hero.y < (*p)){

		if (left)		{ ptr_enemy->ldf = 4; ptr_enemy->sprite = (u8*) &g_demon_lateral_izquierda; }
		else if (right)	{ ptr_enemy->ldf = 5; ptr_enemy->sprite = (u8*) &g_demon_lateral_izquierda; }
		else 			{ ptr_enemy->ldf = 0; ptr_enemy->sprite = (u8*) &g_demon_trasera; }
	}
	// Check down
	else {

		if (left)		{ ptr_enemy->ldf = 6; ptr_enemy->sprite = (u8*) &g_demon_inferior_izquierda; }
		else if (right)	{ ptr_enemy->ldf = 7; ptr_enemy->sprite = (u8*) &g_demon_inferior_derecha; }
		else 			{ ptr_enemy->ldf = 1; ptr_enemy->sprite = (u8*) &g_demon_frontal; }
	}

	// Objective shot
	shot(2, enemy);
}

void fill_enemy(TEnemy* p, u8 x, u8 y){
	p->x = x;
	p->y = y;
	p->lives++;
	p->perform_action = chase_hero;
	p->stpa = 0;
}

void spawn_enemy(u8* enemy){
	u8 tile_x,tile1_y,tile2_y;
	u8 enemy_x = (*enemy), enemy_y = (*(enemy+1));
	u8* ptilemap = (u8*) &g_building;
	
	for(u8 i=0;i<MAX_ENEMIES_SCREEN;++i){
		if(enemies[i].lives == 0){
			
			//DERECHA
			tile_x = enemy_x+ENEMY_WIDTH;
			tile1_y = enemy_y;
			tile2_y = enemy_y+ENEMY_HEIGHT/2;

			if (ptilemap[pixel_to_tile(tile_x, tile1_y)] == PROVISIONAL_FLOOR_TILE_ID
			&& ptilemap[pixel_to_tile(tile_x, tile2_y)] == PROVISIONAL_FLOOR_TILE_ID){
				fill_enemy(&enemies[i], tile_x, tile1_y);
				return;
			}

			//ARRIBA
			tile_x -= ENEMY_WIDTH;
			tile1_y -= ENEMY_HEIGHT;
			tile2_y -= ENEMY_HEIGHT;

			if (ptilemap[pixel_to_tile(tile_x, tile1_y)] == PROVISIONAL_FLOOR_TILE_ID
			&& ptilemap[pixel_to_tile(tile_x, tile2_y)] == PROVISIONAL_FLOOR_TILE_ID){
				fill_enemy(&enemies[i], tile_x, tile1_y);
				return;
			}

			//IZQUIERDA
			tile_x = enemy_x-ENEMY_WIDTH;
			tile1_y = enemy_y;
			tile2_y = enemy_y+ENEMY_HEIGHT/2;

			if (ptilemap[pixel_to_tile(tile_x, tile1_y)] == PROVISIONAL_FLOOR_TILE_ID
			&& ptilemap[pixel_to_tile(tile_x, tile2_y)] == PROVISIONAL_FLOOR_TILE_ID){
				fill_enemy(&enemies[i], tile_x, tile1_y);
				return;
			}

			//ABAJO
			tile_x = enemy_x;
			tile1_y = enemy_y+ENEMY_HEIGHT;
			tile2_y = enemy_y+ENEMY_HEIGHT+ENEMY_HEIGHT/2;

			if (ptilemap[pixel_to_tile(tile_x, tile1_y)] == PROVISIONAL_FLOOR_TILE_ID
			&& ptilemap[pixel_to_tile(tile_x, tile2_y)] == PROVISIONAL_FLOOR_TILE_ID){
				fill_enemy(&enemies[i], tile_x, tile1_y);
				return;
			}
		}
	}
}

void chase_and_shot(u8* enemy){ //Wizard Loquillo
	
	TEnemy* ptr_enemy = (TEnemy*) enemy;
	chase_hero(enemy);

	if (ptr_enemy->ldf == 0)		{ ptr_enemy->sprite = (u8*) &g_wizard_trasera; }				// Up
	else if (ptr_enemy->ldf == 1)	{ ptr_enemy->sprite = (u8*) &g_wizard_frontal; }				// Down
	else if (ptr_enemy->ldf == 2)	{ ptr_enemy->sprite = (u8*) &g_wizard_izquierda; }				// Left
	else if (ptr_enemy->ldf == 3)	{ ptr_enemy->sprite = (u8*) &g_wizard_derecha; }				// Right
	else if (ptr_enemy->ldf == 4)	{ ptr_enemy->sprite = (u8*) &g_wizard_superior_izquierda; }		// Up-left
	else if (ptr_enemy->ldf == 5)	{ ptr_enemy->sprite = (u8*) &g_wizard_superior_derecha; }		// Up-right
	else if (ptr_enemy->ldf == 6)	{ ptr_enemy->sprite = (u8*) &g_wizard_frontal; }				// Down-left
	else if (ptr_enemy->ldf == 7)	{ ptr_enemy->sprite = (u8*) &g_wizard_frontal; }				// Down-right
	
	shot(1, enemy);
}

/*void just_objective_shot(u8* enemy){ // Demon loquillo

}*/

void chase_hero(u8* enemy){ //Fantasmita
	bool left = false, right = false;
	u8* p = enemy;
	u8* ptilemap = (u8*) &g_building;
	TEnemy* ptr_enemy = (TEnemy*) enemy;
	
	u8 tile1_x = 0;
	u8 tile1_y = 0;
	u8 tile2_x = 0;
	u8 tile2_y = 0;

	// Erase tile
	ptilemap[pixel_to_tile((*p), *(p + 1))] = PROVISIONAL_FLOOR_TILE_ID;
	ptilemap[pixel_to_tile((*p), *(p + 1) + ENEMY_SPEED_Y)] = PROVISIONAL_FLOOR_TILE_ID;


	// Check left
	if (hero.x < (*p)){

		tile1_x = (*p) - ENEMY_SPEED_X;
		tile1_y = *(p + 1);

		tile2_x = (*p) - ENEMY_SPEED_X;
		tile2_y = *(p + 1) + ENEMY_SPEED_Y;

		if (ptilemap[pixel_to_tile(tile1_x, tile1_y)] == PROVISIONAL_FLOOR_TILE_ID
			&& ptilemap[pixel_to_tile(tile2_x, tile2_y)] == PROVISIONAL_FLOOR_TILE_ID){

			(*p) -= ENEMY_SPEED_X;
		}

		ptr_enemy->ldf = 2;
		ptr_enemy->sprite = (u8*) &g_crab_izquierda;
		left = true;
	}
	// Check right
	else {

		tile1_x = (*p) + ENEMY_SPEED_X;
		tile1_y = *(p + 1);

		tile2_x = (*p) + ENEMY_SPEED_X;
		tile2_y = *(p + 1) + ENEMY_SPEED_Y;

		// Look up the tilemap to check if there is an obstacle in our next location
		if (ptilemap[pixel_to_tile(tile1_x, tile1_y)] == PROVISIONAL_FLOOR_TILE_ID
			&& ptilemap[pixel_to_tile(tile2_x, tile2_y)] == PROVISIONAL_FLOOR_TILE_ID){
			
			(*p) += ENEMY_SPEED_X;
		}

		ptr_enemy->ldf = 3;
		ptr_enemy->sprite = (u8*) &g_crab_derecha;
		right = true;
	}

	p++;

	// Check up
	if (hero.y < (*p)){

		tile1_x = *(p - 1);
		tile1_y = (*p) - ENEMY_SPEED_Y;

		// Look up the tilemap to check if there is an obstacle in our next location
		if (ptilemap[pixel_to_tile(tile1_x, tile1_y)] == PROVISIONAL_FLOOR_TILE_ID){
			
			(*p) -= ENEMY_SPEED_Y;
		}

		if (left)		{ ptr_enemy->ldf = 4; ptr_enemy->sprite = (u8*) &g_crab_superior_izquierda; }
		else if (right)	{ ptr_enemy->ldf = 5; ptr_enemy->sprite = (u8*) &g_crab_superior_derecha; }
		else 			{ ptr_enemy->ldf = 0; ptr_enemy->sprite = (u8*) &g_crab_trasera;}
	}
	// Check down
	else {

		tile1_x = *(p - 1);
		tile1_y = (*p) + ENEMY_HEIGHT;

		// Look up the tilemap to check if there is an obstacle in our next location
		if (ptilemap[pixel_to_tile(tile1_x, tile1_y)] == PROVISIONAL_FLOOR_TILE_ID){

			(*p) += ENEMY_SPEED_Y;
		}

		if (left)		{ ptr_enemy->ldf = 6; ptr_enemy->sprite = (u8*) &g_crab_frontal; }
		else if (right)	{ ptr_enemy->ldf = 7; ptr_enemy->sprite = (u8*) &g_crab_frontal; }
		else 			{ ptr_enemy->ldf = 1; ptr_enemy->sprite = (u8*) &g_crab_frontal; }
	}

	ptilemap[pixel_to_tile(*(p - 1), (*p))] = PROVISIONAL_ENEMY_OCUPIED_TILE_ID;
	ptilemap[pixel_to_tile(*(p - 1), (*p) + ENEMY_SPEED_Y)] = PROVISIONAL_ENEMY_OCUPIED_TILE_ID;
}

void increase_heal(u8* picked){
	u8* p = picked;
	(*p)++;
	hero.lives++;
	print_health();
}

void drop_health(u8* enemy){
	u8* p;
	TObject* pe;
	if(cpct_getRandom_lcg_u8(0) < 50){
		for(u8 i = 0;i<MAX_OBJECTS_SCREEN;i++){
			if(objects[i].picked == 1){
				p = (u8*)&objects[i];
				pe = (TObject*)&objects[i];
				pe->perform_action = increase_heal;
				(*p) = (*enemy);
				p++;
				enemy++;
				(*p) = (*enemy);
				p++;
				(*p)--;
				break;
			}
		}
	}
}

void update_enemies(){
	u8* p;
	u8* p2;
	check_collision_enemies_hero();

	if(current_iteration == 30){
		current_iteration = 0;
	}

	for(u8 i = current_iteration; i < current_iteration+MAX_NUMBER_OF_UPDATED_ENEMYS; ++i){
		if(enemies[i].lives > 0){
				p = &enemies[i].ctpa;
				p2 = &enemies[i].stpa;
			if((*p) >= (*p2)){
				enemies[i].perform_action((u8*)&enemies[i]);
				(*p) = 0;
			}else{
				(*p)++;
			}
		}
	}

	current_iteration += MAX_NUMBER_OF_UPDATED_ENEMYS;

}
	
void draw_enemies(){
	for(u8 i=0;i<MAX_ENEMIES_SCREEN;++i){
		if(enemies[i].lives > 0){
			if (video_isInsideViewport(screen_x, screen_y, enemies[i].x, enemies[i].y, ENEMY_WIDTH, ENEMY_HEIGHT)){
		    	//cpct_drawSolidBox(cpct_getScreenPtr(video_getBackBufferPtr(), enemies[i].x - screen_x, enemies[i].y - screen_y), 200, ENEMY_WIDTH, ENEMY_HEIGHT);
				cpct_drawSpriteMasked(enemies[i].sprite, cpct_getScreenPtr(video_getBackBufferPtr(), enemies[i].x - screen_x, enemies[i].y - screen_y), ENEMY_WIDTH, ENEMY_HEIGHT);
	    	}
		}
	}
}

void draw_objects(){
	for(u8 i=0;i<MAX_OBJECTS_SCREEN;++i){
		if(objects[i].picked == 0){
			if (video_isInsideViewport(screen_x, screen_y, objects[i].x, objects[i].y, OBJECT_WIDTH, OBJECT_HEIGHT)){
		    	cpct_drawSolidBox(cpct_getScreenPtr(video_getBackBufferPtr(), objects[i].x - screen_x, objects[i].y - screen_y), 53, OBJECT_WIDTH, OBJECT_HEIGHT);
	    	}
		}
	}
}

void init_hero(){
	u8** p = &current_map;

	(*p) = p_to_maps[0];
	current_index = 0;

	hero.x = HERO_START_X_RELATIVE;
	hero.y = HERO_START_Y_RELATIVE;
	hero.lives = 1;
	hero.sprite = (u8*) &g_hero_frontal;
}

void next_level(){
	u8** p = &current_map;
	u8* pvmem = cpct_getScreenPtr(video_getBackBufferPtr(), 16, 85);
	u8 s10 = ((current_index + 2) / 10) + 48;
	u8 s1 = ((current_index + 2) % 10) + 48;
	(*p) = p_to_maps[++current_index];

	cpct_memset(video_getBackBufferPtr(), 0, 16000);
	//cpct_drawSolidBox(video_getBackBufferPtr(), 0, VIEWPORT_WB, VIEWPORT_HP);
	cpct_drawStringM0("Next level: ", pvmem, NEXT_LEVEL_FOREGROUND_COLOR, NEXT_LEVEL_BACKGROUND_COLOR);

	pvmem = cpct_getScreenPtr(video_getBackBufferPtr(), 62, 85);
	cpct_drawCharM0(pvmem, NEXT_LEVEL_FOREGROUND_COLOR, NEXT_LEVEL_BACKGROUND_COLOR, s10);

	pvmem = cpct_getScreenPtr(video_getBackBufferPtr(), 67, 85);
	cpct_drawCharM0(pvmem, NEXT_LEVEL_FOREGROUND_COLOR, NEXT_LEVEL_BACKGROUND_COLOR, s1);

	video_switchBuffers();

	//cpct_drawStringM0("SCORE", INIT_LETTERS_SCORE_POSITION, SCORE_FOREGROUND_COLOR, SCORE_BACKGROUND_COLOR);
	for (u16 i = 0; i < 800; i++){

		cpct_waitVSYNC();
	}

	map_load((u8*)current_map);
}

void perform_teletransportation(){
	u8 hero_x_tiles = hero.x/TILE_W, hero_y_tiles = hero.y/TILE_HP;
	u8 tile_x, tile_y;
	TPortal* p;

	for(u8 i = 0;i < MAX_PORTALS_SCREEN;++i){
		if(portals[i].x == hero_x_tiles && portals[i].y == hero_y_tiles){
			p = &portals[i];
			break;
		}
	}

	tile_x = p->x_to;
	tile_y = p->y_to;
	hero.x = p->x_to*4;
	hero.y = p->y_to*8;

	if(tile_x < START_TILE_SCROLL_X){
		scroll_x = 0;
	}else if(tile_x >= START_TILE_SCROLL_X && tile_x <= END_TILE_SCROLL_X){
		scroll_x = tile_x - START_TILE_SCROLL_X;
	}else{
		scroll_x = 12;
	}


	if(tile_y < START_TILE_SCROLL_Y){
		scroll_y = 0;
	}else if(tile_y >= START_TILE_SCROLL_Y && tile_y <= END_TILE_SCROLL_Y){
		scroll_y = tile_y - START_TILE_SCROLL_Y;
	}else{
		scroll_y = 14;
	}	
	screen_x = scroll_x * TILE_W;
	screen_y = scroll_y * TILE_HP;
	offset = scroll_y*g_building_W + scroll_x;
}

void update_hero(){
	bool left = false, right = false;
	u8 tile1_x = 0;
	u8 tile1_y = 0;
	u8 tile2_x = 0;
	u8 tile2_y = 0;
	u8 aux;
	u8* ptilemap = (u8*) &g_building;

	if(hero.teletransportation != 0){
		hero.teletransportation=0;
		perform_teletransportation();
	}

	cpct_scanKeyboard_f();

	// Check user input and update offset accordingly (OPQA for movement)
	// Use (x, y) coordinates of the upper-left tile of the viewport to determine 
	// valid movements (those that maintain viewport inside g_building tilemap boundaries).
	// Size of the viewport (VIEWPORT_W, VIEWPORT_H) is used to check boundaries.
	// Offset value update:
	//    - Right-Left movements select previous-next tile in the tilemap, so offset requires 
	//      to be updated (-1 for left), (+1 for right).
	//    - Up-Down movements want to select one tile up or one tile down. However, as the tilemap
	//      is stored as a 2D-array, it means that one tile up or down is 1 row away in memory
	//      (Each row is stored in memory after the previous row). Therefore, to select up-down
	//      tiles in memory, offset requires to be updated (-g_building_W for up), (+g_building_W for down)
	//

	//cpct_scanKeyboard_f();
	if (cpct_isKeyPressed(keys.left)){

		tile1_x = hero.x - HERO_SPEED_X;
		tile1_y = hero.y;

		tile2_x = hero.x - HERO_SPEED_X;
		tile2_y = hero.y + HERO_SPEED_Y;

		aux = ptilemap[pixel_to_tile(tile1_x, tile1_y)];

		
		if(aux == PROVISIONAL_PORTAL_END){
			next_level();
		}else 
		// Look up the tilemap to check if there is a wall in our next location
		if 	(aux != PROVISIONAL_OBSTACLE_TILE_ID  
			&& ptilemap[pixel_to_tile(tile2_x, tile2_y)] != PROVISIONAL_OBSTACLE_TILE_ID){

			if(aux == PROVISIONAL_PORTAL_LOCAL){
				hero.teletransportation = 1;
			}

			if (scroll_x > 0 && hero.x - screen_x <= HERO_START_X_RELATIVE){

				--scroll_x;
				--offset;
				screen_x = scroll_x * TILE_W;

			}
			hero.x -= HERO_SPEED_X;
		}

		hero.ldf = 2;
		hero.sprite = (u8*) &g_hero_lateral_izquierda;
		left = true;
		if(hero.teletransportation) return;
	}

	if (cpct_isKeyPressed(keys.right)){

		tile1_x = hero.x + HERO_SPEED_X;
		tile1_y = hero.y;

		tile2_x = hero.x + HERO_SPEED_X;
		tile2_y = hero.y + HERO_SPEED_Y;

		aux = ptilemap[pixel_to_tile(tile1_x, tile1_y)];
		
		if(aux == PROVISIONAL_PORTAL_END){
			next_level();
		}else
		// Look up the tilemap to check if there is an obstacle in our next location
		if (aux != PROVISIONAL_OBSTACLE_TILE_ID 
			&& ptilemap[pixel_to_tile(tile2_x, tile2_y)] != PROVISIONAL_OBSTACLE_TILE_ID){

			if(aux == PROVISIONAL_PORTAL_LOCAL){
				hero.teletransportation = 1;
			}

			if (hero.x - screen_x >= HERO_START_X_RELATIVE && scroll_x < g_building_W - VIEWPORT_W){

				++scroll_x;
				++offset;
				screen_x = scroll_x * TILE_W;
			}
			hero.x += HERO_SPEED_X;
		}

		hero.ldf = 3;
		hero.sprite = (u8*) &g_hero_lateral_derecha;
		right = true;
		if(hero.teletransportation) return;
	}

	if (cpct_isKeyPressed(keys.up)){

		tile1_x = hero.x;
		tile1_y = hero.y - HERO_SPEED_Y;

		aux = ptilemap[pixel_to_tile(tile1_x, tile1_y)];

		if(aux == PROVISIONAL_PORTAL_END){
			next_level();
		}else
		// Look up the tilemap to check if there is an obstacle in our next location
		if (aux != PROVISIONAL_OBSTACLE_TILE_ID){

			if(aux == PROVISIONAL_PORTAL_LOCAL){
				hero.teletransportation = 1;
			}

			if (scroll_y > 0 && hero.y - screen_y <= HERO_START_Y_RELATIVE){

				--scroll_y;
				offset -= g_building_W;
				screen_y = (scroll_y * TILE_HP);
			}
			hero.y -= HERO_SPEED_Y;
		}

		if (left)		{ hero.ldf = 4; hero.sprite = (u8*) &g_hero_superior_izquierda; }
		else if (right)	{ hero.ldf = 5; hero.sprite = (u8*) &g_hero_superior_derecha; }
		else 			{ hero.ldf = 0; hero.sprite = (u8*) &g_hero_trasera; }
	}

	if (cpct_isKeyPressed(keys.down)){

		tile1_x = hero.x;
		tile1_y = hero.y + HERO_HEIGHT;

		aux = ptilemap[pixel_to_tile(tile1_x, tile1_y)];

		if(aux == PROVISIONAL_PORTAL_END){
			next_level();
		}else
		// Look up the tilemap to check if there is an obstacle in our next location
		if (aux != PROVISIONAL_OBSTACLE_TILE_ID){

			if(ptilemap[pixel_to_tile(tile1_x, tile1_y-HERO_HEIGHT/2)] == PROVISIONAL_PORTAL_LOCAL){
				hero.teletransportation = 1;
			}

			if (hero.y - screen_y >= HERO_START_Y_RELATIVE && scroll_y < g_building_H - VIEWPORT_H){

				++scroll_y;
				offset += g_building_W;
				screen_y = (scroll_y * TILE_HP);
			}
			hero.y += HERO_SPEED_Y;
		}

		if (left)		{ hero.ldf = 6; hero.sprite = (u8*) &g_hero_frontal; }
		else if (right)	{ hero.ldf = 7; hero.sprite = (u8*) &g_hero_frontal; }
		else 			{ hero.ldf = 1; hero.sprite = (u8*) &g_hero_frontal; }
	}

	if(cpct_isKeyPressed(keys.shot)){
		shot(0, (u8*) &hero);
	}
	check_collision_hero_objects();
}

void draw_hero(){
	//cpct_drawSolidBox(cpct_getScreenPtr(video_getBackBufferPtr(),hero.x - screen_x, hero.y - screen_y), 130, HERO_WIDTH, HERO_HEIGHT);
	cpct_drawSpriteMasked(hero.sprite, cpct_getScreenPtr(video_getBackBufferPtr(), hero.x - screen_x, hero.y - screen_y), HERO_WIDTH, HERO_HEIGHT);
}

////////////////////////////////////////////////////////////////////////////////////////////
//	
//  bullets_array: array a updatear.  
//	size: tamaño del array.
//	n_bullets: puntero al contador de balas, puede ser el de enemy o el hero.
//
////////////////////////////////////////////////////////////////////////////////////////////

void update_bullets_aux(TBullet* bullets_array, u8 size, u8* n_bullets){
	u8 i = size;
	TBullet* bullets_pointer = bullets_array;
	// Comprobamos si colisiona:
	do {
		if (bullets_pointer[i].x != 0xFF){

			if ( ! video_isInsideViewport(screen_x, screen_y, bullets_pointer[i].x, bullets_pointer[i].y, BULLETS_WIDTH, BULLETS_HEIGHT)){

				bullets_pointer[i].x = 0xFF;
				n_bullets--;
				continue;
			}

			// 0: up, 1: down, 2: left, 3: right, 4:up-left, 5:up-right, 6:down-left, 7:down-right
			switch(bullets_pointer[i].dir){
				case 0:
					if(bullets_pointer[i].y - screen_y > 7){
						bullets_pointer[i].y -= 8;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 1:
					if(bullets_pointer[i].y - screen_y <= (VIEWPORT_HP - BULLETS_HEIGHT - 8)){
						bullets_pointer[i].y += 8;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 2:
					if(bullets_pointer[i].x - screen_x > 3){
						bullets_pointer[i].x -= 4;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 3:
					if(bullets_pointer[i].x - screen_x < (VIEWPORT_WB - BULLETS_WIDTH + 3)){
						bullets_pointer[i].x += 4;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 4:
					if(bullets_pointer[i].y - screen_y != 0){
						bullets_pointer[i].y -= 8;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
						break;
					}
					if(bullets_pointer[i].x - screen_x > 3){
						bullets_pointer[i].x -= 4;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 5:
					if(bullets_pointer[i].y - screen_y != 0){
						bullets_pointer[i].y -= 8;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
						break;
					}
					if(bullets_pointer[i].x - screen_x < (VIEWPORT_WB - BULLETS_WIDTH + 3)){
						bullets_pointer[i].x += 4;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 6:
					if(bullets_pointer[i].y - screen_y <= (VIEWPORT_HP - BULLETS_HEIGHT - 8)){
						bullets_pointer[i].y += 8;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
						break;
					}
					if(bullets_pointer[i].x - screen_x > 3){
						bullets_pointer[i].x -= 4;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 7:
					if(bullets_pointer[i].y - screen_y <= (VIEWPORT_HP - BULLETS_HEIGHT - 8)){
						bullets_pointer[i].y += 8;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
						break;
					}
					if(bullets_pointer[i].x - screen_x < (VIEWPORT_WB - BULLETS_WIDTH + 3)){
						bullets_pointer[i].x += 4;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				default:
					break;
			}
		}
    } while(i--);
}

void update_objective_bullets(){

	TOBullet* obullet;

	for (int i = 0; i < MAX_NUMBER_OBJECTIVE_BULLETS; i++){

		obullet = &bullets_enemies_objective[i];

		// If bullet is in use
		if (obullet->x != null){

			// Check the direction of the bullet: If increment is positive, start < end
			if (obullet->increment > 0){

				// If bullet has not reached the target
				if (obullet->x < obullet->x_end){

					obullet->x += obullet->increment;
					obullet->y = obullet->y_end + obullet->m * obullet->x - obullet->m * obullet->x_end;
				}
				else {

					obullet->x = null;
				}
			}
			// If increment is not positive, start > end
			else {

				// If bullet has not reached the target
				if (obullet->x > obullet->x_end){

					obullet->x += obullet->increment;
					obullet->y = obullet->y_end + obullet->m * obullet->x - obullet->m * obullet->x_end;
				}
				else {

					obullet->x = null;
				}

			}
		}
	}
}

bool check_collision_items(u8* first, u8 fheight, u8 fwidth, u8* second, u8 sheight, u8 swidth){
	
	// first apunta a FirstEntity.x
	// second apunta a SecondEntity.x

	//Comprobar colisión horizontal
	if( ( (*first)+fwidth > (*second) ) && ( (*second)+swidth > (*first) ) ){
		//Colisionado horizontalmente
		
		first++;
		second++;
		// first apunta a FirstEntity.y
		// second apunta a SecondEntity.y


		//Comprobar colisión vertical
		if(( (*first)+fheight > (*second) ) && ( (*second)+sheight > (*first) )){
			// Colisionan verticalmente
			return true;
		}
		return false;
	}

	return false;
}

void check_collision_bullet_hero(){
	u8* p;
	u8* ptilemap = (u8*) &g_building;

	for(u8 i=0;i<MAX_ENEMIES_SCREEN;++i){
		if(enemies[i].lives != 0 && bullet_hero.x != 0xFF){
			if(check_collision_items((u8*)&bullet_hero, BULLETS_HEIGHT, BULLETS_WIDTH, (u8*)&enemies[i], ENEMY_HEIGHT, ENEMY_WIDTH)){
				//Le quitamos una vida al enemigo
				p = &enemies[i].lives;
				--(*p);
				if((*p) == 0){

					// Erase tile
					ptilemap[pixel_to_tile(enemies[i].x, enemies[i].y)] = PROVISIONAL_FLOOR_TILE_ID;
					ptilemap[pixel_to_tile(enemies[i].x, enemies[i].y + ENEMY_SPEED_Y)] = PROVISIONAL_FLOOR_TILE_ID;

					drop_health((u8*)&enemies[i]);
				}
				// Eliminamos la bala de la pantalla
				p = (u8*)&bullet_hero;
				(*p) = 0xFF;
				// Restamos uno al contador de balas del hero
				p = (u8*)n_hero_bullets_on_screen;
				(*p)--;

				//Aumentamos el score en 10
				hero.score += 10;
				//Y lo actualizamos
				print_score();
			}
		}
	}
}

void check_collision_bullets_enemies(){
	u8* pbullet;
	for(u8 i=0;i<MAX_BULLETS_ENEMY;++i){
		if(bullets_enemies[i].x != 0xFF && check_collision_items((u8*)&bullets_enemies[i], BULLETS_WIDTH, BULLETS_HEIGHT, (u8*)&hero, HERO_WIDTH, HERO_HEIGHT)){
			pbullet = (u8*)&bullets_enemies[i];
			(*pbullet) = 0xFF;
			hero.lives--;
		}
	}
}

void check_collision_enemies_hero(){
	TEnemy* p;
	u8* ptilemap = (u8*) g_building;

	for(u8 i=0;i<MAX_ENEMIES_SCREEN;++i){
		if(enemies[i].lives > 0 && check_collision_items((u8*)&enemies[i], ENEMY_HEIGHT, ENEMY_WIDTH, (u8*)&hero, HERO_HEIGHT, HERO_WIDTH)){
			p = &enemies[i];
			
			p->lives = 0;
			ptilemap[pixel_to_tile(p->x, p->y)] = PROVISIONAL_FLOOR_TILE_ID;
			ptilemap[pixel_to_tile(p->x, p->y + ENEMY_SPEED_Y)] = PROVISIONAL_FLOOR_TILE_ID;


			hero.lives--;		
			print_health();
		}
	}	
}

void check_collision_hero_objects(){
	u8* pbullet;
	for(u8 i=0;i<MAX_OBJECTS_SCREEN;++i){
		if(objects[i].picked == 0 && check_collision_items((u8*)&objects[i], OBJECT_HEIGHT, OBJECT_WIDTH, (u8*)&hero, HERO_HEIGHT, HERO_WIDTH)){
			objects[i].perform_action(&objects[i].picked);
		}
	}	
}

void update_bullets(){
	u8* n_bullets = (u8*)n_hero_bullets_on_screen;
	if((*n_bullets)){
		update_bullets_aux(&bullet_hero, MAX_BULLETS_HERO-1, n_bullets);
		check_collision_bullet_hero();
	}

	update_objective_bullets();


	/*n_bullets = (u8*)n_enemy_bullets_on_screen;
	if((*n_bullets)){
		check_collision_bullets_enemies();
		update_bullets_aux(bullets_enemies, MAX_BULLETS_ENEMY-1, n_bullets);
	}*/
}

void draw_portals(){
	//16
	//21
	for(u8 i=0;i<MAX_PORTALS_SCREEN;++i){

	}

}

void draw_bullets(){

	// 0: up, 1: down, 2: left, 3: right, 4:up-left, 5:up-right, 6:down-left, 
	if (bullet_hero.x != 0xFF){
		cpct_drawSolidBox(cpct_getScreenPtr(video_getBackBufferPtr(), bullet_hero.x - screen_x, bullet_hero.y - screen_y), 30, BULLETS_WIDTH, BULLETS_HEIGHT);	
	}

	for (int i = 0; i < MAX_NUMBER_OBJECTIVE_BULLETS; i++){

		if (bullets_enemies_objective[i].x != null){

			cpct_drawSolidBox(cpct_getScreenPtr(video_getBackBufferPtr(), bullets_enemies_objective[i].x - screen_x, bullets_enemies_objective[i].y - screen_y), 30, BULLETS_WIDTH, BULLETS_HEIGHT);	
		}
	}
	
	/*u8 i = MAX_BULLETS_HERO-1;
	do {
		if(bullets_hero[i].x != 0xFF){
			cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, bullets_hero[i].x, bullets_hero[i].y), 30, BULLETS_WIDTH, BULLETS_HEIGHT);	
		}
    } while(i--);*/

}

// who: 0 -> hero, who: 1 -> enemy, who: 2 -> enemy with objetive shot
void shot(u8 who, u8* entity){
	u8* n_bullets;
	if(who == 1){
		u8 i = MAX_BULLETS_ENEMY-1;
		do{
			if(bullets_enemies[i].x == 0xFF){
				n_bullets = (u8*)n_enemy_bullets_on_screen;
				(*n_bullets)++;
				fill_spot_bullet(&bullets_enemies[i], entity);
				break;
			}
		}while(i--);
	}
	else if (who == 0){
		if(bullet_hero.x == 0xFF){
			n_bullets = (u8*)n_hero_bullets_on_screen;
			(*n_bullets)++;
			fill_spot_bullet(&bullet_hero, entity);		
		}
	}
	// Objective shot
	else {

		u8 i = MAX_NUMBER_OBJECTIVE_BULLETS - 1;

		do {

			if (bullets_enemies_objective[i].x == 0xFF){

				n_bullets = (u8*)n_enemy_objective_bullets_on_screen;
				(*n_bullets)++;
				fill_spot_objective_bullet(&bullets_enemies_objective[i], (TEnemy*) entity);
				break;
			}
		}
		while (i--);
	}
	
}

void fill_spot_objective_bullet(TOBullet* obullet, TEnemy* enemy){

	// Set start and end of the objective bullet
	obullet->x = enemy->x;
	obullet->y = enemy->y;
	obullet->x_end = hero.x + HERO_WIDTH / 2;
	obullet->y_end = hero.y + HERO_HEIGHT / 2;

	// Check if start is lower than end. In that case, increment will be a positive integer
	if (obullet->x < obullet->x_end){

		obullet->increment = BULLETS_SPEED_X;
	}
	// Otherwise, it will be a negative integer
	else {

		obullet->increment = -BULLETS_SPEED_X;
	}

	// Calculate the slope
	obullet->m = (obullet->y_end - obullet->y) / (obullet->x_end - obullet->x);
}

void fill_spot_bullet(TBullet* array_bullets, u8* shooter){
	

	/////////////////////////////////////////////////////////////////////////////////////
	//
	// Firstly tranform the input array to *u8 (All data members are u8) so we can increase the value manualy 
	// allowing the compiler optimize the assembly generated.
	// Order of data:
	//	u8 x
	//	u8 y 
	// 	u8 ldf
	//	u8 px
	//	u8 py
	//
	//////////////////////////////////////////////////////////////////////////////////////

	//cpct_memcpy((void*)array_bullets, (void*)hero, (u16)5); 93t less bytes
	//0: hero,   1: enemy

	u8* raw_pointer_bullets = (u8*) array_bullets;

	u8 	increment_x = bullet_table_x[*(shooter+2)],
		increment_y = bullet_table_y[*(shooter+2)];

	(*raw_pointer_bullets) = (*shooter) + increment_x;
	
	raw_pointer_bullets++;
	shooter++;

	(*raw_pointer_bullets) = (*shooter) + increment_y;
	
	raw_pointer_bullets++;
	shooter++;

	(*raw_pointer_bullets) = (*shooter); //72t more bytes
}



