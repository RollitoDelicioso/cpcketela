#include "entity.h"

#include "state/game.h"
#include "video/video.h"
#include <tilemap/tileset.h>            // Automatically generated tileset arrays declarations
#include <tilemap/building.h>           // Automatically generated g_building tilemap declarations
//#include <maps/frame_updown.h>      // Automatically generated g_frame_ud tilemap declarations
//#include <maps/frame_leftright.h>   // Automatically generated g_frame_lr tilemap declarations


THero hero;
const TEnemy enemies[MAX_ENEMIES_SCREEN] = {{60, 100, 5}, {30, 50, 5}};
const TBullets bullet_hero = {0xFF, 0, 0};
const TBullets bullets_enemies[MAX_BULLETS_ENEMY] = {{0xFF, 0, 0}, {0xFF, 0, 0}, {0xFF, 0, 0}};
const u8 n_hero_bullets_on_screen = 0;
const u8 n_enemy_bullets_on_screen = 0;

void update_enemies_aux(){

}

void draw_enemies_aux(TEnemy* enemy){

	if (video_isInsideViewport(screen_x, screen_y, enemy->x, enemy->y, ENEMY_WIDTH, ENEMY_HEIGHT)){

		cpct_drawSolidBox(cpct_getScreenPtr(video_getBackBufferPtr(), enemy->x - screen_x, enemy->y - screen_y), 200, ENEMY_WIDTH, ENEMY_HEIGHT);
	}

	/*cpct_drawSolidBox(
		cpct_getScreenPtr(video_getBackBufferPtr(), enemy->x, enemy->y), 200, ENEMY_WIDTH, ENEMY_HEIGHT);*/
}	

void update_enemies(){

}

void draw_enemies(){
	for(u8 i=0;i<MAX_ENEMIES_SCREEN;++i){
		if(enemies[i].lives != 0)
			draw_enemies_aux(&enemies[i]);
	}
}


void init_hero(){
	hero.x = HERO_START_X_RELATIVE;
	hero.y = HERO_START_Y_RELATIVE;
	hero.lives = 5;
}

void update_hero(){
	bool left = false, right = false;

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

		if (scroll_x > 0 && hero.x - screen_x <= HERO_START_X_RELATIVE){

			--scroll_x;
			--offset;
			hero.x -= 4;
			screen_x = scroll_x * TILE_W;

			//screen_y = (scroll_y * TILE_HP);
		}
		else if (hero.x - screen_x > 0){

			hero.x -= 2;
		}

		hero.ldf = 2;
		left = true;
	}

	if (cpct_isKeyPressed(keys.right)){

		if (hero.x - screen_x >= HERO_START_X_RELATIVE && scroll_x < g_building_W - VIEWPORT_W){

			++scroll_x;
			++offset;
			hero.x += 4;
			screen_x = scroll_x * TILE_W;
			//screen_y = (scroll_y * TILE_HP);
		}
		else if (hero.x - screen_x < (VIEWPORT_WB - HERO_WIDTH - 1)){

			hero.x += 2;
		}

		hero.ldf = 3;
		right = true;
	}

	if (cpct_isKeyPressed(keys.up)){

		if (scroll_y > 0 && hero.y - screen_y <= HERO_START_Y_RELATIVE){

			--scroll_y;
			offset -= g_building_W;
			//screen_x = scroll_x * (TILE_WP / 2);
			hero.y -= 8;
			screen_y = (scroll_y * TILE_HP);
		}
		else if (hero.y - screen_y > 0){

			hero.y -= 8;
		}

		if (left)		{ hero.ldf = 4; }
		else if (right)	{ hero.ldf = 5; }
		else 			{ hero.ldf = 0; }
	}

	if (cpct_isKeyPressed(keys.down)){

		if (hero.y - screen_y >= HERO_START_Y_RELATIVE && scroll_y < g_building_H - VIEWPORT_H){

			++scroll_y;
			offset += g_building_W;
			//screen_x = scroll_x * (TILE_WP / 2);
			hero.y += 8;
			screen_y = (scroll_y * TILE_HP);
		}
		else if (hero.y - screen_y < (VIEWPORT_HP - HERO_HEIGHT)){

			hero.y += 8;
		}

		if (left)		{ hero.ldf = 6; }
		else if (right)	{ hero.ldf = 7; }
		else 			{ hero.ldf = 1; }
	}

	if(cpct_isKeyPressed(keys.shot)){
		shot(0);
	}
}

void draw_hero(){

	// Calcular relativa de hero
	u8 hero_x_relative = hero.x - screen_x;
	u8 hero_y_relative = hero.y - screen_y;

	cpct_drawSolidBox(cpct_getScreenPtr(video_getBackBufferPtr(), hero_x_relative, hero_y_relative), 130, HERO_WIDTH, HERO_HEIGHT);
}



////////////////////////////////////////////////////////////////////////////////////////////
//	
//  bullets_array: array a updatear.  
//	size: tamaño del array.
//	n_bullets: puntero al contador de balas, puede ser el de enemy o el hero.
//
////////////////////////////////////////////////////////////////////////////////////////////

void update_bullets_aux(TBullets* bullets_array, u8 size, u8* n_bullets){
	u8 i = size;
	TBullets* bullets_pointer = bullets_array;

	// Comprobamos si colisiona:
	// Primero con enemigos-heroe, luego con paredes.
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
	for(u8 j=0;j<MAX_ENEMIES_SCREEN;++j){
		if(enemies[j].lives != 0 && bullet_hero.x != 0xFF){
			if(check_collision_items((u8*)&bullet_hero, BULLETS_HEIGHT, BULLETS_WIDTH, (u8*)&enemies[j], ENEMY_HEIGHT, ENEMY_WIDTH)){
				//Le quitamos una vida al enemigo
				p = &enemies[j].lives;
				(*p)--;
				// Eliminamos la bala de la pantalla
				p = (u8*)&bullet_hero;
				(*p) = 0xFF;
				// Restamos uno al contador de balas del hero
				p = (u8*)n_hero_bullets_on_screen;
				(*p)--;
			}
		}
	}
}

void check_collision_bullets_enemies(){
	u8* pbullet;
	for(u8 i=0;i<MAX_BULLETS_ENEMY;++i){
		if(bullets_enemies[i].x != 0xFF && check_collision_items((u8*)bullets_enemies[i], BULLETS_WIDTH, BULLETS_HEIGHT, (u8*)hero, HERO_WIDTH, HERO_HEIGHT)){
			pbullet = (u8*)&bullets_enemies[i];
			(*pbullet) = 0xFF;
			hero.lives--;
		}
	}
}

void update_bullets(){
	u8* n_bullets = (u8*)n_hero_bullets_on_screen;
	if((*n_bullets)){
		update_bullets_aux(&bullet_hero, MAX_BULLETS_HERO-1, n_bullets);
		check_collision_bullet_hero();
	}
	/*n_bullets = (u8*)n_enemy_bullets_on_screen;
	if((*n_bullets)){
		check_collision_bullets_enemies();
		update_bullets_aux(bullets_enemies, MAX_BULLETS_ENEMY-1, n_bullets);
	}*/
}

void draw_bullets(){

	// bullet_hero.dir
	// 0: up, 1: down, 2: left, 3: right, 4:up-left, 5:up-right, 6:down-left, 

	if (bullet_hero.x != 0xFF){

		/*switch (bullet_hero.dir){

			case 0:
				cpct_drawSolidBox(cpct_getScreenPtr(video_getBackBufferPtr(), bullet_hero.x, bullet_hero.y + screen_y), 30, BULLETS_WIDTH, BULLETS_HEIGHT);
				break;
			case 1:
				cpct_drawSolidBox(cpct_getScreenPtr(video_getBackBufferPtr(), bullet_hero.x, bullet_hero.y - screen_y), 30, BULLETS_WIDTH, BULLETS_HEIGHT);
				break;
			case 2:
				cpct_drawSolidBox(cpct_getScreenPtr(video_getBackBufferPtr(), bullet_hero.x - screen_x, bullet_hero.y), 30, BULLETS_WIDTH, BULLETS_HEIGHT);
				break;
			case 3:
				cpct_drawSolidBox(cpct_getScreenPtr(video_getBackBufferPtr(), bullet_hero.x + screen_x, bullet_hero.y), 30, BULLETS_WIDTH, BULLETS_HEIGHT);
				break;
		}*/
		cpct_drawSolidBox(cpct_getScreenPtr(video_getBackBufferPtr(), bullet_hero.x - screen_x, bullet_hero.y - screen_y), 30, BULLETS_WIDTH, BULLETS_HEIGHT);	
	}
	
	/*u8 i = MAX_BULLETS_HERO-1;
	do {
		if(bullets_hero[i].x != 0xFF){
			cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, bullets_hero[i].x, bullets_hero[i].y), 30, BULLETS_WIDTH, BULLETS_HEIGHT);	
		}
    } while(i--);*/

}

// who: 0 -> hero, who: 1 -> enemy
void shot(u8 who){
	u8* n_bullets;
	if(who){
		u8 i = MAX_BULLETS_ENEMY-1;
		do{
			if(bullets_enemies[i].x == 0xFF){
				n_bullets = (u8*)n_enemy_bullets_on_screen;
				(*n_bullets)++;
				fill_spot_bullet(&bullets_enemies[i]);
				break;
			}
		}while(i--);
	}else{
		if(bullet_hero.x == 0xFF){
			n_bullets = (u8*)n_hero_bullets_on_screen;
			(*n_bullets)++;
			fill_spot_bullet(&bullet_hero);		
		}
	}

	
}


void fill_spot_bullet(TBullets* array_bullets){
	
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
	
	u8* raw_pointer_bullets = (u8*) array_bullets; 
	(*raw_pointer_bullets) = hero.x;
	raw_pointer_bullets += 1;
	(*raw_pointer_bullets) = hero.y;
	raw_pointer_bullets += 1;
	(*raw_pointer_bullets) = hero.ldf; //72t more bytes
}