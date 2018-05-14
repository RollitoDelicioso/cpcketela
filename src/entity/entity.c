#include "entity.h"

// Member functions
void init_hero(THero* hero){
	hero->x = 30;
	hero->y = 30;
	hero->px = 0;
	hero->py = 0;
	hero->width = 0;
	hero->height = 0;
}

void update_hero(THero* hero){
	
	cpct_scanKeyboard();
	
	if(cpct_isKeyPressed(keys.up)){
		if(hero->y != 0 )
			hero->y -= 2;
	}else if(cpct_isKeyPressed(keys.down)){
		if(hero->y-(200-10) != 0 ) //200 max height screen - 10 height hero (pixels)
			hero->y += 2;
	}
	if(cpct_isKeyPressed(keys.left)){
		if(hero->x != 0 )
			hero->x--;
	}else if(cpct_isKeyPressed(keys.right)){
		if(hero->x-(80-10) != 0) //80 max width screen - 10 width hero (bytes)
			hero->x++;
	}
}

void draw_hero(THero* hero){
	cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, hero->x, hero->y), 130, 1, 8);
}

void erase_hero(THero* hero){
	cpct_drawSolidBox(cpct_getScreenPtr(CPCT_VMEM_START, hero->x, hero->y), 0, 1, 8);	
}