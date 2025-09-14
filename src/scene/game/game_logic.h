#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <gb/gb.h>
#include "game.h"

void game_spawn_item(UBYTE type, UINT8 x, UINT8 y);
void game_conveyor_belt_update(void);
UBYTE game_get_tile_at_position(UINT8 x, UINT8 y);
item_t *game_get_free_item_slot(void);

#endif // GAME_LOGIC_H