#include <cpctelera.h>
#include "maps/maps.h"
#include "constants.h"
#include "entity/entity.h"
#include <tilemap/tileset.h>            // Automatically generated tileset arrays declarations
#include <tilemap/building.h>           // Automatically generated g_building tilemap declarations

//const u8 index;

u8* const p_to_maps[2] = {maps_000, maps_001};

// Maps
const u8 maps_000[24+(4*14)+(4*4)+(2*5)] = {
	0, //Suelo
	1, // Muros
	14, // Suelo falso
	
	18, // Número de obstaculos
	OBSTACLE_CREATE_RECTANGLE(0,0,31,31)
	1, 13, 28, 13,
	9, 8, 9, 28,
	12, 22, 30, 22,
	19, 6, 19, 10,
	21, 25, 21, 30,
	
	5, 5, 30, 5,
	13,27,28,27,
	21,16,21,21,
	12,9,28,9,
	3,18,18,18,
	
	5,16,5,28,
	15,3,15,6,
	27,14,27,19,
	2,9,8,9,

	4, // Número de portales
	3, 19, 28, 1, // Portal1 hacia portal2 índice 0
	28, 1, 10, 12, // Portal2 hacia portal1 índice 1
	10, 12, 27, 30,
	27, 30, 3, 19,

	30, 1, //Portal Final
	
	5, // Número de generadores
	4,8,
	20*4,28*8,
	8*4,19*8,
	10*4,14*8,
	20*4,6*8
};
const u8 maps_001[24+(4*10)+(4*2)+(2*1)] = {
	0, //Suelo
	4, // Muros
	14, // Suelo falso
	
	14, // Número de obstaculos
	OBSTACLE_CREATE_RECTANGLE(0,0,31,31)
	1, 13, 28, 13,
	9, 8, 9, 28,
	12, 22, 30, 22,
	19, 6, 19, 10,
	21, 25, 21, 30,
	
	5, 5, 30, 5,
	13,27,28,27,
	21,16,21,21,
	12,9,28,9,
	3,18,18,18,

	2, // Número de portales
	3, 19, 28, 1, // Portal1 hacia portal2 índice 0
	28, 1, 10, 12, // Portal2 hacia portal1 índice 1
	30, 1, //Portal Final
	1, // Número de generadores
	4,8,
};





void reset_enemies(){
	TEnemy* p;
	for(u8 i=0;i<MAX_ENEMIES_SCREEN;i++){
		p = &enemies[i];
		p->lives = 0;
	}
}

// Functions
void map_load(u8* map){

	// Pointer to tilemap
	u8* ptilemap = (u8*) &g_building;
	TEnemy* enemy_aux_pointer;
	TPortal* portal_aux_pointer;
	u8 obstacles_start_index = 4;
	u8 portals_start_index = map[3]*4 + obstacles_start_index; //24 + 4 == 28
	u8 indice = portals_start_index+1;
	u8 generators_start_index;

	// Change background color
	for (u8 i = 2; i < g_building_H - 1; i++){

		for (u8 j = 2; j < g_building_W - 1; j++){

			ptilemap[i * g_building_W + j] = map[0];
		}
	}

	// Draw obstacles
	for (u8 i = 0; i < map[3]; i++){

		for (u8 j = map[obstacles_start_index]; j <= map[obstacles_start_index + 2]; j++){

			for (u8 k = map[obstacles_start_index + 1]; k <= map[obstacles_start_index + 3]; k++){

				ptilemap[k * g_building_W + j] = map[1];
			}
		}

		obstacles_start_index += 4;
	}
	
	//Draw portals
	for (u8 i = 0; i < map[portals_start_index]; i++){
		//(portals_start_index+1) + i*3
		ptilemap[map[indice+1] * g_building_W + map[indice]] = 16;
		ptilemap[(map[indice+1]+1) * g_building_W + map[indice]] = 21;
		portal_aux_pointer = &portals[i];
		portal_aux_pointer->x = map[indice];
		portal_aux_pointer->y = map[indice+1];
		portal_aux_pointer->x_to = map[indice+2];
		portal_aux_pointer->y_to = map[indice+3];
		indice += 4;
	}

	//Draw final portal
	ptilemap[map[indice+1] * g_building_W + map[indice]] = 18;
	ptilemap[(map[indice+1]+1) * g_building_W + map[indice]] = 23;

	reset_enemies();

	// Fill generators
	indice += 3;
	generators_start_index = indice-1;
	for(u8 i = 0;i < map[generators_start_index];++i){
		enemy_aux_pointer = &enemies[i];
		enemy_aux_pointer->x = map[indice];
		enemy_aux_pointer->y = map[indice+1];
		enemy_aux_pointer->perform_action = spawn_enemy;
		enemy_aux_pointer->ctpa = 0;
		enemy_aux_pointer->lives = 2;
		enemy_aux_pointer->stpa = 10;
		indice += 2;
	}

	// Paint score and health
	print_score();
	print_health();
}