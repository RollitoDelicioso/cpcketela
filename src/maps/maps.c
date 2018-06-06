#include <cpctelera.h>
#include "maps/maps.h"
#include "constants.h"
#include "entity/entity.h"
#include <tilemap/tileset.h>            // Automatically generated tileset arrays declarations
#include <sprites/monster_portal.h>
#include <tilemap/map1.h>           // Automatically generated g_building tilemap declarations
#include <sprites/crab_frontal.h>
#include <sprites/wizard_frontal.h>
#include <sprites/demon_frontal.h>
#include <sprites/heart.h>
#include <sprites/coin.h>



u8* const p_to_maps[6] = {maps_001, maps_002, maps_003, maps_004, maps_005, maps_006};

// Maps
const u8 maps_001[26+(4*18)+(4*4)+(4*2)+(3*9)+(3*2)] = {
	0, //Suelo
	14, // Muros
	1, // Suelo falso
	
	4+18, // Número de obstaculos no diagonales
	OBSTACLE_CREATE_RECTANGLE(0,0,31,31)
	
	OBSTACLE_CREATE_LINE(1,1,6,1)
	OBSTACLE_CREATE_LINE(1,2,6,2)
	OBSTACLE_CREATE_LINE(1,6,6,6)
	OBSTACLE_CREATE_LINE(1,5,6,5)
	OBSTACLE_CREATE_LINE(6,3,6,5)

	OBSTACLE_CREATE_LINE(7,4,11,4)
	OBSTACLE_CREATE_LINE(11,5,11,10)
	OBSTACLE_CREATE_LINE(1,12,8,12)
	OBSTACLE_CREATE_LINE(4,15,7,15)
	OBSTACLE_CREATE_LINE(8,16,15,16)

	OBSTACLE_CREATE_LINE(1,22,8,22)
	OBSTACLE_CREATE_LINE(8,23,18,23)
	OBSTACLE_CREATE_LINE(8,26,8,30)
	OBSTACLE_CREATE_LINE(17,27,20,27)
	OBSTACLE_CREATE_LINE(24,19,24,23)
	
	OBSTACLE_CREATE_LINE(20,11,20,15)
	OBSTACLE_CREATE_LINE(14,8,14,13)
	OBSTACLE_CREATE_LINE(21,30,21,30)

	4, // Número de obstaculos diagonales
	OBSTACLE_CREATE_DIAGONAL_LINE(11,11,25,25)
	OBSTACLE_CREATE_DIAGONAL_LINE(14,4,30,20)
	OBSTACLE_CREATE_DIAGONAL_LINE(24,12,29,7)
	OBSTACLE_CREATE_DIAGONAL_LINE(13,30,16,27)


	2, // Número de portales
	5, 3, 28, 13,
	28, 13, 5, 3,

	1, 3, //Portal Final
	
	9, // Número de generadores
	ENEMY_CREATE(4,10,3)
	ENEMY_CREATE(5,18,1)
	ENEMY_CREATE(13,7,1)
	ENEMY_CREATE(16,13,1)
	ENEMY_CREATE(15,20,1)
	
	ENEMY_CREATE(20,28,1)
	ENEMY_CREATE(22,4,1)
	ENEMY_CREATE(22,18,1)
	ENEMY_CREATE(28,10,1)

	2, // Number of golds
	2,14,2,
	12,14,1,
};

const u8 maps_002[26+(4*13)+(4*9)+(4*4)+(3*7)+(3*0)] = {
	7, //Suelo
	6, // Muros
	8, // Suelo falso
	
	4+13, // Número de obstaculos no diagonales
	OBSTACLE_CREATE_RECTANGLE(0,0,31,31)
	
	OBSTACLE_CREATE_LINE(9,1,9,5)
	OBSTACLE_CREATE_LINE(12,5,20,5)
	OBSTACLE_CREATE_LINE(24,3,24,9)
	OBSTACLE_CREATE_LINE(22,9,22,21)
	OBSTACLE_CREATE_LINE(27,19,30,16)
	
	OBSTACLE_CREATE_LINE(28,22,30,22)
	OBSTACLE_CREATE_LINE(28,23,28,27)
	OBSTACLE_CREATE_LINE(14,13,19,13)
	OBSTACLE_CREATE_LINE(10,9,13,9)
	OBSTACLE_CREATE_LINE(3,7,3,25)
	
	OBSTACLE_CREATE_LINE(8,25,11,25)
	OBSTACLE_CREATE_LINE(8,28,17,28)
	OBSTACLE_CREATE_LINE(24,28,24,28)

	9, // Número de obstaculos diagonales
	OBSTACLE_CREATE_DIAGONAL_LINE(1,1,28,28)
	OBSTACLE_CREATE_DIAGONAL_LINE(5,10,23,28)
	OBSTACLE_CREATE_DIAGONAL_LINE(4,14,18,28)
	OBSTACLE_CREATE_DIAGONAL_LINE(26,14,30,18)
	OBSTACLE_CREATE_DIAGONAL_LINE(26,6,26,8)
	
	OBSTACLE_CREATE_DIAGONAL_LINE(4,28,15,17)
	OBSTACLE_CREATE_DIAGONAL_LINE(14,12,23,3)
	OBSTACLE_CREATE_DIAGONAL_LINE(26,13,28,11)
	OBSTACLE_CREATE_DIAGONAL_LINE(26,5,30,1)

	4, // Número de portales
	13, 20, 30, 16,
	30, 16, 13, 20,
	16, 14, 30, 2,
	30, 2, 16, 14,

	13, 11, //Portal Final
	
	7, // Número de generadores
	ENEMY_CREATE(2,15,1)
	ENEMY_CREATE(1,20,1)
	ENEMY_CREATE(2,27,1)
	ENEMY_CREATE(9,26,1)
	ENEMY_CREATE(12,2,1)
	
	ENEMY_CREATE(17,24,1)
	ENEMY_CREATE(25,8,1)

	0, // Number of golds

};

const u8 maps_003[26+(4*25)+(4*5)+(4*0)+(3*10)+(3*0)] = {
	3, //Suelo
	25, // Muros
	4, // Suelo falso
	
	4 + 25, // Número de obstaculos no diagonales
	OBSTACLE_CREATE_RECTANGLE(0,0,31,31)
	
	OBSTACLE_CREATE_LINE(9,1,23,1)
	OBSTACLE_CREATE_LINE(9,2,23,2)
	OBSTACLE_CREATE_LINE(9,3,9,16)
	OBSTACLE_CREATE_LINE(9,16,19,16)
	OBSTACLE_CREATE_LINE(19,5,19,16)
	
	OBSTACLE_CREATE_LINE(11,5,19,5)
	OBSTACLE_CREATE_LINE(11,5,11,13)
	OBSTACLE_CREATE_LINE(12,5,12,13)
	OBSTACLE_CREATE_LINE(13,12,13,13)
	OBSTACLE_CREATE_LINE(14,8,14,13)
	
	OBSTACLE_CREATE_LINE(15,8,15,13)
	OBSTACLE_CREATE_LINE(16,8,16,13)
	OBSTACLE_CREATE_LINE(17,8,17,13)
	OBSTACLE_CREATE_LINE(21,3,21,22)
	OBSTACLE_CREATE_LINE(22,3,22,22)
	
	OBSTACLE_CREATE_LINE(23,3,23,22)
	OBSTACLE_CREATE_LINE(7,19,20,19)
	OBSTACLE_CREATE_LINE(7,20,20,20)
	OBSTACLE_CREATE_LINE(7,21,20,21)
	OBSTACLE_CREATE_LINE(7,22,20,22)

	OBSTACLE_CREATE_LINE(7,3,7,18)
	OBSTACLE_CREATE_LINE(5,1,5,25)
	OBSTACLE_CREATE_LINE(5,25,27,25)
	OBSTACLE_CREATE_LINE(27,4,27,25)
	OBSTACLE_CREATE_LINE(1,30,1,30)


	5, // Número de obstaculos diagonales
	OBSTACLE_CREATE_DIAGONAL_LINE(3,28,5,26)
	OBSTACLE_CREATE_DIAGONAL_LINE(9,26,11,28)
	OBSTACLE_CREATE_DIAGONAL_LINE(16,28,18,30)
	OBSTACLE_CREATE_DIAGONAL_LINE(22,28,24,26)
	OBSTACLE_CREATE_DIAGONAL_LINE(28,28,30,30)

	0, // Número de portales

	2, 2, //Portal Final

	10, // Número de generadores
	ENEMY_CREATE(1,9,1)
	ENEMY_CREATE(2,14,1)
	ENEMY_CREATE(2,23,1)
	ENEMY_CREATE(8,29,1)
	ENEMY_CREATE(25,29,1)
	
	ENEMY_CREATE(28,9,1)
	ENEMY_CREATE(20,23,1)
	ENEMY_CREATE(6,15,1)
	ENEMY_CREATE(10,7,1)
	ENEMY_CREATE(20,13,1)

	0, // Number of golds

};

const u8 maps_004[26+(4*5)+(4*0)+(4*0)+(3*8)+(3*0)] = {
	7, //Suelo
	13, // Muros
	8, // Suelo falso
	
	4 + 5, // Número de obstaculos no diagonales
	OBSTACLE_CREATE_RECTANGLE(0,0,31,31)
	
	OBSTACLE_CREATE_LINE(1,5,28,5)
	OBSTACLE_CREATE_LINE(3,10,30,10)
	OBSTACLE_CREATE_LINE(1,16,26,16)
	OBSTACLE_CREATE_LINE(4,21,30,21)
	OBSTACLE_CREATE_LINE(1,27,27,27)

	0, // Número de obstaculos diagonales

	0, // Número de portales

	1, 28, //Portal Final

	8, // Número de generadores
	ENEMY_CREATE(6,6,1)
	ENEMY_CREATE(25,2,1)
	ENEMY_CREATE(12,13,1)
	ENEMY_CREATE(24,13,1)
	ENEMY_CREATE(9,19,1)
	
	ENEMY_CREATE(3,24,1)
	ENEMY_CREATE(21,23,1)
	ENEMY_CREATE(14,29,1)

	0, // Number of golds

};

const u8 maps_005[26+(4*22)+(4*4)+(4*4)+(3*8)+(3*0)] = {
	7, //Suelo
	13, // Muros
	8, // Suelo falso
	
	4 + 22, // Número de obstaculos no diagonales
	OBSTACLE_CREATE_RECTANGLE(0,0,31,31)
	
	OBSTACLE_CREATE_LINE(1,15,30,15)
	OBSTACLE_CREATE_LINE(5,20,10,20)
	OBSTACLE_CREATE_LINE(5,20,5,21)
	OBSTACLE_CREATE_LINE(5,24,5,26)
	OBSTACLE_CREATE_LINE(6,26,9,26)

	OBSTACLE_CREATE_LINE(10,23,10,15)
	OBSTACLE_CREATE_LINE(15,1,15,30)
	OBSTACLE_CREATE_LINE(3,6,6,6)
	OBSTACLE_CREATE_LINE(6,4,6,5)
	OBSTACLE_CREATE_LINE(16,10,21,10)

	OBSTACLE_CREATE_LINE(21,11,21,11)
	OBSTACLE_CREATE_LINE(5,20,10,20)
	OBSTACLE_CREATE_LINE(16,23,16,23)
	OBSTACLE_CREATE_LINE(18,22,18,22)
	OBSTACLE_CREATE_LINE(20,20,20,20)

	OBSTACLE_CREATE_LINE(22,18,22,18)
	OBSTACLE_CREATE_LINE(23,16,23,16)
	OBSTACLE_CREATE_LINE(18,28,18,28)
	OBSTACLE_CREATE_LINE(21,27,21,27)
	OBSTACLE_CREATE_LINE(25,25,25,25)

	OBSTACLE_CREATE_LINE(27,23,27,23)
	OBSTACLE_CREATE_LINE(28,20,28,20)

	4, // Número de obstaculos diagonales
	OBSTACLE_CREATE_DIAGONAL_LINE(1,16,5,20)
	OBSTACLE_CREATE_DIAGONAL_LINE(10,26,14,30)
	OBSTACLE_CREATE_DIAGONAL_LINE(4,1,14,11)
	OBSTACLE_CREATE_DIAGONAL_LINE(21,1,30,10)

	4, // Número de portales
	14, 16, 16, 13,
	16, 16, 14, 13,
	16, 13, 16, 16,
	14, 13, 14, 16,

	3, 3, //Portal Final

	8, // Número de generadores
	ENEMY_CREATE(1,3,1)
	ENEMY_CREATE(5,10,1)
	ENEMY_CREATE(7,22,1)
	ENEMY_CREATE(9,17,1)
	ENEMY_CREATE(18,4,1)
	
	ENEMY_CREATE(18,24,1)
	ENEMY_CREATE(23,20,1)
	ENEMY_CREATE(24,11,1)
	
	0, // Number of golds

};

const u8 maps_006[26+(4*4)+(4*2)+(4*4)+(3*10)+(3*0)] = {
	22, //Suelo
	11, // Muros
	27, // Suelo falso
	
	4 + 4, // Número de obstaculos no diagonales
	OBSTACLE_CREATE_RECTANGLE(0,0,31,31)
	
	OBSTACLE_CREATE_LINE(1,7,28,7)
	OBSTACLE_CREATE_LINE(28,8,28,26)
	OBSTACLE_CREATE_LINE(5,13,14,13)
	OBSTACLE_CREATE_LINE(1,26,17,26)

	2, // Número de obstaculos diagonales
	OBSTACLE_CREATE_DIAGONAL_LINE(1,10,17,26)
	OBSTACLE_CREATE_DIAGONAL_LINE(14,13,27,26)

	4, // Número de portales
	2, 28, 2, 16,
	2, 16, 2, 16,
	10, 23, 6, 9,
	6, 9, 6, 9,

	24, 14, //Portal Final

	10, // Número de generadores
	ENEMY_CREATE(17,2,1)
	ENEMY_CREATE(26,4,1)
	ENEMY_CREATE(29,15,1)
	ENEMY_CREATE(30,19,1)
	ENEMY_CREATE(29,23,1)
	
	ENEMY_CREATE(15,19,1)
	ENEMY_CREATE(13,28,1)
	ENEMY_CREATE(5,20,1)
	ENEMY_CREATE(10,9,1)
	ENEMY_CREATE(21,10,1)

	0, // Number of golds
};


void reset_enemies(){
	u8* p;
	for(u8 i=0;i<MAX_ENEMIES_SCREEN;i++){
		p = &enemies[i].lives;
		(*p) = 0;
	}
}

void reset_objects(){
	u8* p;
	for(u8 i=0;i<MAX_OBJECTS_SCREEN;i++){
		p = &objects[i].picked;
		(*p) = 1;
	}
}

// Functions
void map_load(u8* map){

	// Pointer to tilemap
	u8* ptilemap = (u8*) &g_building;
	TEnemy* enemy_aux_pointer;
	TPortal* portal_aux_pointer;
	TObject* object_aux_pointer;
	u8 index = 4;
	u8 n_d_obstacles, n_nd_obstacles, n_portals, n_enemies, n_objects;
	u8 direction; // 0 Down, 1 Up
	u8 k_aux, j_aux;
	
	// Change background color
	for (u8 i = 1; i < g_building_H - 1; i++){

		for (u8 j = 1; j < g_building_W - 1; j++){

			ptilemap[i * g_building_W + j] = map[0];
		}
	}

	// Draw no diagonal obstacles
	n_nd_obstacles = map[3];
	for (u8 i = 0; i < n_nd_obstacles; i++){

		for (u8 j = map[index]; j <= map[index + 2]; j++){

			for (u8 k = map[index + 1]; k <= map[index + 3]; k++){

				ptilemap[k * g_building_W + j] = map[1];
			}
		}

		index += 4;
	}
	
	// Draw diagonal obstacles
	n_d_obstacles = map[index];
	index++;
	for (u8 i = 0; i < n_d_obstacles; i++){
		if(map[index + 1] > map[index + 3]){
			direction = 1; // up
		}else{
			direction = 0; // down
		}
		k_aux = map[index+1];
		j_aux = map[index];
		for (u8 j = map[index]; j <= map[index + 2]; j++){
			if(direction == 1){
				ptilemap[(k_aux-(j-j_aux)) * g_building_W + j] = map[1];

			}else{
				ptilemap[(k_aux+(j-j_aux)) * g_building_W + j] = map[1];
			}
		}
		index += 4;
	}



	//Draw portals
	n_portals = map[index];
	index++;
	for (u8 i = 0; i < n_portals; i++){
		ptilemap[map[index+1] * g_building_W + map[index]] = 16;
		ptilemap[(map[index+1]+1) * g_building_W + map[index]] = 21;
		portal_aux_pointer = &portals[i];
		portal_aux_pointer->x = map[index];
		portal_aux_pointer->y = map[index+1];
		portal_aux_pointer->x_to = map[index+2];
		portal_aux_pointer->y_to = map[index+3];
		index += 4;
	}

	//Draw final portal
	ptilemap[map[index+1] * g_building_W + map[index]] = 18;
	ptilemap[(map[index+1]+1) * g_building_W + map[index]] = 23;

	reset_enemies();
	reset_objects();

	// Fill enemies
	index += 2;
	n_enemies = map[index];
	index++;
	for(u8 i = 0;i < n_enemies;++i){		
		enemy_aux_pointer = &enemies[i];

		if(map[index+2] == 1){
			enemy_aux_pointer->perform_action = spawn_enemy;		
			enemy_aux_pointer->lives = 2;
			enemy_aux_pointer->stpa = 5;
			enemy_aux_pointer->sprite = (u8*) &g_monster_portal;
		}else if(map[index+2] == 2){
			enemy_aux_pointer->perform_action = chase_hero;		
			enemy_aux_pointer->lives = 1;
			enemy_aux_pointer->stpa = 2;
			enemy_aux_pointer->sprite = (u8*) &g_crab_frontal;
		}else if(map[index+2] == 3){
			enemy_aux_pointer->perform_action = chase_and_shot;		
			enemy_aux_pointer->lives = 1;
			enemy_aux_pointer->stpa = 3;
			enemy_aux_pointer->sprite = (u8*) &g_wizard_frontal;
		}else{
			enemy_aux_pointer->perform_action = shot_objective;		
			enemy_aux_pointer->lives = 1;
			enemy_aux_pointer->stpa = 4;
			enemy_aux_pointer->sprite = (u8*) &g_demon_frontal;
		}

		enemy_aux_pointer->x = map[index]*4;
		enemy_aux_pointer->y = map[index+1]*8;
		enemy_aux_pointer->ctpa = 0;
		index += 3;
	}
	

	// Fill objects
	n_objects = map[index];
	index++;
	for(u8 i = 0;i < n_objects;++i){
		object_aux_pointer = &objects[i];

		if(map[index+2] == 1){
			object_aux_pointer->perform_action = increase_heal;		
			object_aux_pointer->picked = 0;
			object_aux_pointer->sprite = (u8*) &g_heart;
		}else{
			object_aux_pointer->perform_action = add_score;		
			object_aux_pointer->picked = 0;
			object_aux_pointer->sprite = (u8*) &g_coin;
		}

		object_aux_pointer->x = map[index]*4;
		object_aux_pointer->y = map[index+1]*8;
		index += 3;
	}
}