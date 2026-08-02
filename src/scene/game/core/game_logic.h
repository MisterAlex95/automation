#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <gb/gb.h>
#include "game.h"

void game_spawn_tile(UBYTE type, UINT8 x, UINT8 y);
void game_conveyor_belt_update(void);
void game_miners_update(void);
void game_chest_update(void);

#endif // GAME_LOGIC_H
