#ifndef GAME_H
#define GAME_H

#include "assets/item.h"
#include "constants.h"
#include <gb/gb.h>
#include <stdio.h>

typedef struct {
  UBYTE id;
  UBYTE direction;
  UBYTE pos_x, pos_y;
  UBYTE type;
  UBYTE sprite_id;
} item_t;

typedef struct {
  UBYTE active;
  UBYTE tile_x;
  UBYTE tile_y;
  UBYTE direction;
  UINT16 cooldown;
  UINT16 rate;
} miner_t;

typedef struct {
  item_t items[MAX_ITEMS];
  UBYTE cursor_x, cursor_y, cursor_direction;
  UBYTE paused;
  UBYTE menu_state;
  UBYTE selected_tile;
  UBYTE miner_count;
} game_t;

void game_init(void);
void game_update_game(void);
UBYTE *game_get_active_items(void);
miner_t *get_miners(void);
void game_update_list_of_active_items(void);

extern game_t game;

#endif // GAME_H
