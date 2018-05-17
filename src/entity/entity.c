#include "entity.h"

THero hero;
TEnemy enemies[MAX_ENEMIES_SCREEN];
const TBullets bullets_hero[MAX_BULLETS_HERO] = { {0xFF,0,0,0,0}, {0xFF,0,0,0,0}, {0xFF,0,0,0,0}, {0xFF,0,0,0,0}, {0xFF,0,0,0,0}};
TBullets bullets_enemies[MAX_BULLETS_ENEMY];

void init_hero(){
	hero.x = 30;
	hero.y = 30;
	hero.px = 0;
	hero.py = 0;
}

void update_hero(){
	static u8 cycles_to_shot;
	bool up = false, down = false;

	cpct_scanKeyboard();
	cpct_setBorder(2);

	// 0: up, 1: down, 2: left, 3: right, 4:up-left, 5:up-right, 6:down-left, 7:down-right
	if(cpct_isKeyPressed(keys.up)){
		if(hero.y != 0 ){
			hero.y -= 2;
			hero.ldf = 0;
			up = true;
		}
	}else if(cpct_isKeyPressed(keys.down)){
		if(hero.y < (200-HERO_HEIGHT)){ //200 max height screen - height hero	
			hero.y += 2;
			hero.ldf = 1;
			down = true;
		}
	}
	if(cpct_isKeyPressed(keys.left)){
		if(hero.x != 0 ){
			hero.x--;
			if(up){
				hero.ldf = 4;
			}else if(down){
				hero.ldf = 6;
			}else{
				hero.ldf = 2;
			}
		}
	}else if(cpct_isKeyPressed(keys.right)){
		if(hero.x < (80-HERO_WIDTH)){ //80 max width screen - width hero
			hero.x++;
			if(up){
				hero.ldf = 5;
			}else if(down){
				hero.ldf = 7;
			}else{
				hero.ldf = 3;
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

void erase_hero(){
	cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, hero.x, hero.y), 0, HERO_WIDTH, HERO_HEIGHT);	
}

void update_bullets(){
	u8 i = MAX_BULLETS_HERO-1;
	TBullets* bullets_hero_pointer = bullets_hero;
	do {
		if(bullets_hero_pointer[i].x != 0xFF){
			switch(bullets_hero_pointer[i].direction){
				// 0: up, 1: down, 2: left, 3: right, 4:up-left, 5:up-right, 6:down-left, 7:down-right
				case 0:
					if(bullets_hero_pointer[i].y != 0){
						bullets_hero_pointer[i].y -= 2;
					}else{
						bullets_hero_pointer[i].x = 0xFF;
					}
					break;
				case 1:
					if(bullets_hero_pointer[i].y < (200-BULLETS_HEIGHT)){
						bullets_hero_pointer[i].y+= 2;
					}else{
						bullets_hero_pointer[i].x = 0xFF;
					}
					break;
				case 2:
					if(bullets_hero_pointer[i].x != 0){
						bullets_hero_pointer[i].x--;
					}else{
						bullets_hero_pointer[i].x = 0xFF;
					}
					break;
				case 3:
					if(bullets_hero_pointer[i].x < (80-BULLETS_WIDTH)){
						bullets_hero_pointer[i].x++;
					}else{
						bullets_hero_pointer[i].x = 0xFF;
					}
					break;
				case 4:
					if(bullets_hero_pointer[i].y != 0){
						bullets_hero_pointer[i].y -= 2;
					}else{
						bullets_hero_pointer[i].x = 0xFF;
						break;
					}
					if(bullets_hero_pointer[i].x != 0){
						bullets_hero_pointer[i].x--;
					}else{
						bullets_hero_pointer[i].x = 0xFF;
					}
					break;
				case 5:
					if(bullets_hero_pointer[i].y != 0){
						bullets_hero_pointer[i].y -= 2;
					}else{
						bullets_hero_pointer[i].x = 0xFF;
						break;
					}
					if(bullets_hero_pointer[i].x < (80-BULLETS_WIDTH)){
						bullets_hero_pointer[i].x++;
					}else{
						bullets_hero_pointer[i].x = 0xFF;
					}
					break;
				case 6:
					if(bullets_hero_pointer[i].y < (200-BULLETS_HEIGHT)){
						bullets_hero_pointer[i].y += 2;
					}else{
						bullets_hero_pointer[i].x = 0xFF;
						break;
					}
					if(bullets_hero_pointer[i].x != 0){
						bullets_hero_pointer[i].x--;
					}else{
						bullets_hero_pointer[i].x = 0xFF;
					}
					break;
				case 7:
					if(bullets_hero_pointer[i].y < (200-BULLETS_HEIGHT)){
						bullets_hero_pointer[i].y += 2;
					}else{
						bullets_hero_pointer[i].x = 0xFF;
						break;
					}
					if(bullets_hero_pointer[i].x < (80-BULLETS_WIDTH)){
						bullets_hero_pointer[i].x++;
					}else{
						bullets_hero_pointer[i].x = 0xFF;
					}
					break;
				default:
					break;
			}
		}
    } while(i--);
}

void draw_bullets(){
	u8 i = MAX_BULLETS_HERO-1;
	do {
		if(bullets_hero[i].x != 0xFF){
			cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, bullets_hero[i].x, bullets_hero[i].y), 30, BULLETS_WIDTH, BULLETS_HEIGHT);	
		}
    } while(i--);

}

void erase_bullets(){
	u8 i = MAX_BULLETS_HERO-1;
	do {
		if(bullets_hero[i].x != 0xFF){
			cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, bullets_hero[i].x, bullets_hero[i].y), 0, BULLETS_WIDTH, BULLETS_HEIGHT);
		}
    } while(i--);
}

// who: 0 -> hero, who: 1 -> enemy
void shot(u8 who){
	TBullets* bullet_arr = 0;
	u8 i = 0;
	if(who == 1){
		bullet_arr = bullets_enemies;
		i = MAX_BULLETS_ENEMY-1;
	}else{
		bullet_arr = bullets_hero;
		i = MAX_BULLETS_HERO-1;
	}

	do{
		if(bullet_arr[i].x == 0xFF){
			fill_spot(bullet_arr+i);
			break;
		}
	}while(i--);
}


void fill_spot(TBullets* array_bullets){
	
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

	u8* raw_pointer_bullets = (u8*) array_bullets;
	(*raw_pointer_bullets) = hero.x;
	raw_pointer_bullets += 1;
	(*raw_pointer_bullets) = hero.y;
	raw_pointer_bullets += 1;
	(*raw_pointer_bullets) = hero.ldf;
	raw_pointer_bullets += 1;
	(*raw_pointer_bullets) = hero.px;
	raw_pointer_bullets += 1;
	(*raw_pointer_bullets) = hero.py;
}