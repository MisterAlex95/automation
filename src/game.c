#include "game.h"
#include "scene.h"
#include "input.h"
#include "graphics.h"
#include "scene_menu.h"
#include "scene/game/ui/menu/menu.h"
#include "engine/vram_layout.h"

game_t game;
static UBYTE active_items[MAX_ITEMS];
static miner_t miners[MAX_MINERS];

void game_init(void)
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        game.items[i].type = ITEM_TYPE_NONE;
        game.items[i].world_x = 0;
        game.items[i].world_y = 0;
        game.items[i].sprite_id = i + 1; // 0 is reserved for cursor
        game.items[i].id = i;
        game.items[i].direction = DIRECTION_UP;
    }

    game.cursor_x = INITIAL_CURSOR_X;
    game.cursor_y = INITIAL_CURSOR_Y;
    game.cursor_direction = INITIAL_CURSOR_DIRECTION;
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
        miners[i].rate = MINER_DEFAULT_RATE;
        miners[i].cooldown = MINER_DEFAULT_COOLDOWN;
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
    UBYTE count = 0;
    for (UBYTE i = 0; i < MAX_ITEMS; i++)
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
