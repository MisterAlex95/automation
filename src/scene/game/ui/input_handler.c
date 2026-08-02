#include "input_handler.h"
#include "game_cursor.h"
#include "../core/game_logic.h"
#include "game.h"
#include "menu/menu.h"
#include "camera.h"
#include "constants.h"
#include "../core/save_system.h"
#include "scene_menu.h"
#include "scene.h"
#include "input.h"

void input_handle_game_input(UINT8 keys, UINT8 keys_prev)
{
    (void)keys;
    (void)keys_prev;

    UINT8 pressed = input_get_pressed();
    if (!pressed)
        return;

    if (game.won)
    {
        if (pressed & J_START)
            scene_set(&scene_menu);
        return;
    }

    if (pressed & J_UP)
        game_move_cursor(0, -1);
    else if (pressed & J_DOWN)
        game_move_cursor(0, 1);
    else if (pressed & J_LEFT)
        game_move_cursor(-1, 0);
    else if (pressed & J_RIGHT)
        game_move_cursor(1, 0);

    if (pressed & J_A)
    {
        UBYTE wx = cursor_screen_to_world_x(game_get_cursor_x());
        UBYTE wy = cursor_screen_to_world_y(game_get_cursor_y());
        game_spawn_tile(game.selected_tile, wx, wy);
    }
    else if (pressed & J_B)
    {
        game.cursor_direction = (game.cursor_direction + 1) % 4;
    }
    else if (pressed & J_START)
    {
        game.paused = game.paused ? 0 : 1;
        if (game.paused)
            save_game();
    }

    if (pressed & J_SELECT)
        menu_show_tile_selection();
}
