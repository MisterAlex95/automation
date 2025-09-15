#include "game.h"
#include "scene.h"
#include "input.h"
#include "graphics.h"
#include "scene_menu.h"

game_t game;
static UBYTE active_items[MAX_ITEMS];

void game_init(void)
{
    game.score = 0;
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
    game.paused = 0;

    game_update_list_of_active_items();
}

UBYTE *game_get_active_items(void)
{
    return active_items;
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
