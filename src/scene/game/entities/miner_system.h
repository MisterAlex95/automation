#ifndef MINER_SYSTEM_H
#define MINER_SYSTEM_H

#include <gb/gb.h>
#include "game.h"

void miner_update_all(void);
void miner_spawn_item(miner_t *miner);
UBYTE miner_register(UBYTE tile_x, UBYTE tile_y, UBYTE direction);
UBYTE miner_unregister(UBYTE tile_x, UBYTE tile_y);

#endif // MINER_SYSTEM_H
