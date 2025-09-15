#ifndef GAME_H
#define GAME_H

#include <gb/gb.h>
#include <stdio.h>

#define MAX_SCORE 9999
#define MAX_ITEMS 39

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
    uint8_t pos_x, pos_y;
    UBYTE type;
    UBYTE sprite_id;
} item_t;

typedef struct
{
    item_t items[MAX_ITEMS];
    uint8_t cursor_x, cursor_y;
    uint16_t score;
    UBYTE paused;
} game_t;

void game_init(void);
void game_update_game(void);
UBYTE *game_get_active_items(void);
void game_update_list_of_active_items(void);

extern game_t game;

#endif // GAME_H
