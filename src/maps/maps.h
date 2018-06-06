#ifndef _MAPS_H_
#define _MAPS_H_

#include <cpctelera.h>

// Variables that contains pointers to maps
extern u8* const maps[120];

// Maps
extern const u8 maps_000[];
extern const u8 maps_001[];
extern u8* const p_to_maps[];
// Maps will have the following structure:
// [Number of tile] Background color
// [Number of tile], [Number of ranges] (X, Y) (X, Y) | Start - End | Range of 2 sets that represents lines of obstacles to be drawn
// [Number of tile] Sets of (X, Y) positions where portals of creatures must be drawn
// -------------
// NOTE: Every line ends with constant "null" except line 1
// -------------

// Functions
void map_load(u8* map);

#endif