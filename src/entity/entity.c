#include "entity.h"
#include "state/game.h"
#include "video/video.h"
#include <tilemap/tileset.h>            // Automatically generated tileset arrays declarations
#include <tilemap/building.h>           // Automatically generated g_building tilemap declarations
//#include <maps/frame_updown.h>      // Automatically generated g_frame_ud tilemap declarations
//#include <maps/frame_leftright.h>   // Automatically generated g_frame_lr tilemap declarations


THero hero;
const TEnemy enemies[MAX_ENEMIES_SCREEN] = { {60,100,5}, {30,50,5} };
const TBullets bullet_hero = {0xFF,0,0};
const TBullets bullets_enemies[MAX_BULLETS_ENEMY] = {{0xFF,0,0}, {0xFF,0,0}, {0xFF,0,0}};
const u8 n_hero_bullets_on_screen = 0;
const u8 n_enemy_bullets_on_screen = 0;

void update_enemies_aux(){

}

void draw_enemies_aux(TEnemy* enemy){
	cpct_drawSolidBox(
		cpct_getScreenPtr(CPCT_VMEM_START, enemy->x - x_offset, enemy->y - y_offset), 200, ENEMY_WIDTH, ENEMY_HEIGHT);
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
	hero.x = 40;
	hero.y = 30;
	hero.lives = 5;
}

void update_hero(){
	static u8 cycles_to_shot;
	bool left = false, right = false;

	cpct_scanKeyboard();

	// 0: up, 1: down, 2: left, 3: right, 4:up-left, 5:up-right, 6:down-left, 7:down-right
	if(cpct_isKeyPressed(keys.left)){
		if(hero.x != 0 ){
			hero.x--;
			hero.ldf = 2;
			left = true;
		}
	}else if(cpct_isKeyPressed(keys.right)){
		if(hero.x < (80-HERO_WIDTH)){ //80 max width screen - width hero
			hero.x++;
			hero.ldf = 3;
			right = true;	
		}
	}

	if(cpct_isKeyPressed(keys.up)){
		if(hero.y != 0 ){
			hero.y -= 2;
			if(left){
				hero.ldf = 4;
			}else if(right){
				hero.ldf = 5;
			}else{
				hero.ldf = 0;
			}
		}
	}else if(cpct_isKeyPressed(keys.down)){
		if(hero.y < (200-HERO_HEIGHT)){ //200 max height screen - height hero	
			hero.y += 2;
			if(left){
				hero.ldf = 6;
			}else if(right){
				hero.ldf = 7;
			}else{
				hero.ldf = 1;
			}
		}
	}

	if(cycles_to_shot != 0x10){
		cycles_to_shot++;
	}

	if(cpct_isKeyPressed(keys.shot)){
		if(cycles_to_shot == 0x10){
			cycles_to_shot = 0;
			shot(0);
		}
	}
}

void draw_hero(){
	cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, hero.x, hero.y), 130, HERO_WIDTH, HERO_HEIGHT);
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
		if(bullets_pointer[i].x != 0xFF){
			// 0: up, 1: down, 2: left, 3: right, 4:up-left, 5:up-right, 6:down-left, 7:down-right
			switch(bullets_pointer[i].dir){
				case 0:
					if(bullets_pointer[i].y != 0){
						bullets_pointer[i].y -= 2;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 1:
					if(bullets_pointer[i].y < (200-BULLETS_HEIGHT)){
						bullets_pointer[i].y+= 2;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 2:
					if(bullets_pointer[i].x != 0){
						bullets_pointer[i].x--;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 3:
					if(bullets_pointer[i].x < (80-BULLETS_WIDTH)){
						bullets_pointer[i].x++;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 4:
					if(bullets_pointer[i].y != 0){
						bullets_pointer[i].y -= 2;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
						break;
					}
					if(bullets_pointer[i].x != 0){
						bullets_pointer[i].x--;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 5:
					if(bullets_pointer[i].y != 0){
						bullets_pointer[i].y -= 2;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
						break;
					}
					if(bullets_pointer[i].x < (80-BULLETS_WIDTH)){
						bullets_pointer[i].x++;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 6:
					if(bullets_pointer[i].y < (200-BULLETS_HEIGHT)){
						bullets_pointer[i].y += 2;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
						break;
					}
					if(bullets_pointer[i].x != 0){
						bullets_pointer[i].x--;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
					}
					break;
				case 7:
					if(bullets_pointer[i].y < (200-BULLETS_HEIGHT)){
						bullets_pointer[i].y += 2;
					}else{
						bullets_pointer[i].x = 0xFF;
						n_bullets--;
						break;
					}
					if(bullets_pointer[i].x < (80-BULLETS_WIDTH)){
						bullets_pointer[i].x++;
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
	if(bullet_hero.x != 0xFF)
		cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, bullet_hero.x, bullet_hero.y), 30, BULLETS_WIDTH, BULLETS_HEIGHT);	
	
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