#include <types.h>
#include <cpctelera.h>

typedef struct {
	u8 x;
	u8 y;
	u8 px;
	u8 py;
	u8 weight;
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