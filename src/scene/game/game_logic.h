#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <gb/gb.h>
#include "game.h"

item_t *game_spawn_item(UBYTE type, UINT8 x, UINT8 y, UBYTE direction);
void game_spawn_tile(UBYTE type, UINT8 x, UINT8 y);
void game_conveyor_belt_update(void);
void game_miners_update(void);
void game_chest_update(void);
item_t *game_get_free_item_slot(void);

#endif // GAME_LOGIC_H