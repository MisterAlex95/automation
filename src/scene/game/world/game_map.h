#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "constants.h"
#include <gb/gb.h>

// Tile access (world tile coordinates)
UBYTE game_map_get_tile(UBYTE world_tx, UBYTE world_ty);
void game_map_set_tile(UBYTE world_tx, UBYTE world_ty, UBYTE tile_value);

// Legacy pixel-based lookup used by systems mid-migration
UBYTE game_map_get_tile_at_position(UBYTE world_px, UBYTE world_py);

// Sparse item occupancy (scans active items)
UBYTE game_map_count_items_on_tile(UBYTE world_tx, UBYTE world_ty);
UBYTE game_map_has_item_on_tile(UBYTE world_tx, UBYTE world_ty);

// Place/remove buildings. Returns TRUE if tile changed.
UBYTE game_map_place_tile(UBYTE world_tx, UBYTE world_ty, UBYTE tile_type,
                          UBYTE direction);
void game_map_remove_tile(UBYTE world_tx, UBYTE world_ty);

#endif // GAME_MAP_H
