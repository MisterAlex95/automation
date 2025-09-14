#include "game.h"
#include "scene.h"
#include "input.h"
#include "graphics.h"
#include "scene_menu.h"

game_t game;

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
    }
    game.cursor_x = 0;
    game.cursor_y = 0;
}

void game_update_game(void)
{
    scene_update();
}
