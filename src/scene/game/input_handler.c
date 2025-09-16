#include "input_handler.h"
#include "game_cursor.h"
#include "game_logic.h"
#include "graphics.h"
#include "game.h"

void input_handle_game_input(UINT8 keys, UINT8 keys_prev)
{
    (void)keys_prev;

    if (!keys)
        return;

    if (keys & J_UP && !(keys_prev & J_UP))
    {
        game_move_cursor(0, -1);
    }
    else if (keys & J_DOWN && !(keys_prev & J_DOWN))
    {
        game_move_cursor(0, 1);
    }
    else if (keys & J_LEFT && !(keys_prev & J_LEFT))
    {
        game_move_cursor(-1, 0);
    }
    else if (keys & J_RIGHT && !(keys_prev & J_RIGHT))
    {
        game_move_cursor(1, 0);
    }

    if (keys & J_A && !(keys_prev & J_A))
    {
        //        game_spawn_item(ITEM_TYPE_INGOT, game_get_cursor_x(), game_get_cursor_y());
        game_spawn_tile(TILE_TYPE_CONVEYOR, game_get_cursor_x(), game_get_cursor_y());
    }
    else if (keys & J_B && !(keys_prev & J_B))
    {
        game.cursor_direction = (game.cursor_direction + 1) % 4;
    }
    else if (keys & J_START && !(keys_prev & J_START))
    {
        game.paused = !game.paused;
    }
}