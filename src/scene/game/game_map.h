#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "graphics.h"
#include "map.h"

#define MAX_ITEMS_PER_TILE 2

UBYTE tile_buffer[MAP_WIDTH][MAP_HEIGHT][MAX_ITEMS_PER_TILE];
UBYTE tile_count[MAP_WIDTH][MAP_HEIGHT];

UBYTE game_get_tile_at_position(UBYTE x, UBYTE y);
UBYTE *game_get_items_on_tile(UBYTE tile_x, UBYTE tile_y, UBYTE *out_count);
void game_place_item_on_tile(UBYTE item_id, UBYTE tile_x, UBYTE tile_y);
void game_remove_item_from_tile(UBYTE item_id, UBYTE tile_x, UBYTE tile_y);
void game_clear_tile(UBYTE tile_x, UBYTE tile_y);

#endif // GAME_MAP_H