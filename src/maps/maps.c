#include <cpctelera.h>
#include "maps/maps.h"
#include <tilemap/tileset.h>            // Automatically generated tileset arrays declarations
#include <tilemap/building.h>           // Automatically generated g_building tilemap declarations

// Functions
void map_load(u8* map){

	// Pointer to tilemap
	u8* ptilemap = (u8*) &g_building;
	u8 obstacles_start_index = 3;

	// Change background color
	for (u8 i = 1; i < g_building_H - 1; i++){

		for (u8 j = 1; j < g_building_W - 1; j++){

			ptilemap[i * g_building_W + j] = map[0];
		}
	}

	// Draw obstacles
	for (u8 i = 0; i < map[2]; i++){

		for (u8 j = map[obstacles_start_index]; j <= map[obstacles_start_index + 2]; j++){

			for (u8 k = map[obstacles_start_index + 1]; k <= map[obstacles_start_index + 3]; k++){

				ptilemap[k * g_building_W + j] = map[1];
			}
		}

		obstacles_start_index += 4;
	}

}

// Maps
const u8 maps_000[11] = {
	3,
	29, 2,
	5, 5, 7, 5,
	5, 6, 5, 9
};