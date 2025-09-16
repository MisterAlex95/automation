#ifndef GAME_H
#define GAME_H

#include <gb/gb.h>
#include <stdio.h>

#define MAX_SCORE 9999
#define MAX_ITEMS 39

#define TILE_TYPE_NONE 0
#define TILE_TYPE_CONVEYOR 1
#define TILE_TYPE_FACTORY 2

#define ITEM_TYPE_NONE 0
#define ITEM_TYPE_INGOT 1

#define DIRECTION_UP 0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3

typedef struct
{
    UBYTE id;
    UBYTE direction;
    UBYTE pos_x, pos_y;
    UBYTE type;
    UBYTE sprite_id;
} item_t;

typedef struct
{
    item_t items[MAX_ITEMS];
    UBYTE cursor_x, cursor_y, cursor_direction;
    UBYTE paused;
    UBYTE menu_state;
    UBYTE selected_tile;
} game_t;

void game_init(void);
void game_update_game(void);
UBYTE *game_get_active_items(void);
void game_update_list_of_active_items(void);

extern game_t game;

#endif // GAME_H
