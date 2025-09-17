#include "game.h"
#include "scene.h"
#include "input.h"
#include "graphics.h"
#include "scene_menu.h"
#include "menu.h"

game_t game;
static UBYTE active_items[MAX_ITEMS];
static miner_t miners[MAX_MINERS];

void game_init(void)
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        game.items[i].type = ITEM_TYPE_NONE;
        game.items[i].pos_x = 0;
        game.items[i].pos_y = 0;
        game.items[i].sprite_id = 0;
        game.items[i].id = i;
        game.items[i].direction = DIRECTION_UP;
    }
    game.cursor_x = 5;
    game.cursor_y = 5;
    game.cursor_direction = DIRECTION_RIGHT;
    game.paused = 0;
    game.menu_state = MENU_NONE;
    game.selected_tile = TILE_TYPE_NONE;
    game.miner_count = 0;

    for (int i = 0; i < MAX_MINERS; i++)
    {
        miners[i].active = 0;
        miners[i].tile_x = 0;
        miners[i].tile_y = 0;
        miners[i].direction = DIRECTION_UP;
        miners[i].rate = 600;
        miners[i].cooldown = 0;
    }

    game_update_list_of_active_items();
}

UBYTE *game_get_active_items(void)
{
    return active_items;
}

miner_t *get_miners(void)
{
    return miners;
}

void game_update_list_of_active_items(void)
{
    int count = 0;
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        if (game.items[i].type != ITEM_TYPE_NONE)
        {
            active_items[count] = i;
            count++;
        }
    }
    active_items[count] = 0xFF; // end of list marker
}

void game_update_game(void)
{
    scene_update();
}
