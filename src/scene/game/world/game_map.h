#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "graphics.h"
#include "map.h"
#include "constants.h"

#define MAX_ITEMS_PER_TILE 2

extern UBYTE tile_buffer[MAP_WIDTH][MAP_HEIGHT][MAX_ITEMS_PER_TILE];
extern UBYTE tile_count[MAP_WIDTH][MAP_HEIGHT];

// Manage items on the game map
UBYTE game_map_get_tile_at_position(UBYTE x, UBYTE y);
UBYTE *game_map_get_items_on_tile(UBYTE tile_x, UBYTE tile_y, UBYTE *out_count);
void game_map_place_item_on_tile(UBYTE item_id, UBYTE tile_x, UBYTE tile_y);
void game_map_remove_item_from_tile(UBYTE item_id, UBYTE tile_x, UBYTE tile_y);
void game_map_clear_tile(UBYTE tile_x, UBYTE tile_y);

// Manage tiles on the game map
void game_map_place_tile(UBYTE tile_x, UBYTE tile_y, UBYTE tile_type, UBYTE direction);
void game_map_remove_tile(UBYTE tile_x, UBYTE tile_y);

#endif // GAME_MAP_H