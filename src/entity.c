#include <cpctelera.h>
#include <entity.h>

// Member functions
void draw_hero(THero* hero){

	u8* pvideo;
	pvideo = cpct_getScreenPtr(CPCT_VMEM_START, hero->x, hero->y);

	cpct_drawSolidBox(pvideo, 130, 8, 16);
}