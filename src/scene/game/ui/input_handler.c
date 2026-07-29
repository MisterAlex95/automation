#include "input_handler.h"
#include "game_cursor.h"
#include "../core/game_logic.h"
#include "graphics.h"
#include "game.h"
#include "menu/menu.h"
#include "map.h"
#include "camera.h"
#include "constants.h"
#include "../world/viewport.h"
#include "../core/save_system.h"
#include "scene_menu.h"
#include "scene.h"

void input_handle_game_input(UINT8 keys, UINT8 keys_prev)
{
    (void)keys_prev;

    if (!keys)
        return;

    if (game.won)
    {
        if (keys & J_START && !(keys_prev & J_START))
            scene_set(&scene_menu);
        return;
    }

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
        UBYTE wx = cursor_screen_to_world_x(game_get_cursor_x());
        UBYTE wy = cursor_screen_to_world_y(game_get_cursor_y());
        game_spawn_tile(game.selected_tile, wx, wy);
    }
    else if (keys & J_B && !(keys_prev & J_B))
    {
        game.cursor_direction = (game.cursor_direction + 1) % 4;
    }
    else if (keys & J_START && !(keys_prev & J_START))
    {
        game.paused = !game.paused;
        if (game.paused)
            save_game();
    }

    if (keys & J_SELECT && !(keys_prev & J_SELECT))
    {
        menu_show_tile_selection();
    }
}

void menu_handle_input(UINT8 keys, UINT8 keys_prev)
{
    if (game.menu_state == MENU_NONE)
        return;

    if (game.menu_state == MENU_TILE_SELECTION)
    {
        if (keys & J_UP && !(keys_prev & J_UP))
        {
            if (game.selected_tile > 0)
                game.selected_tile = (game.selected_tile - 1) % TILE_TYPE_COUNT;
            menu_show_tile_selection();
        }
        if (keys & J_DOWN && !(keys_prev & J_DOWN))
        {
            game.selected_tile = (game.selected_tile + 1) % TILE_TYPE_COUNT;
            menu_show_tile_selection();
        }
        if (keys & J_A && !(keys_prev & J_A))
        {
            menu_show_orientation_selection();
        }
        if (keys & J_B && !(keys_prev & J_B))
        {
            game.menu_state = MENU_NONE;
            menu_clear();
            viewport_rebuild();
            HIDE_WIN;
        }
    }
    else if (game.menu_state == MENU_ORIENTATION_SELECTION)
    {
        if (keys & J_LEFT && !(keys_prev & J_LEFT))
        {
            game.cursor_direction = (game.cursor_direction + 3) % 4;
            menu_show_orientation_selection();
        }
        if (keys & J_RIGHT && !(keys_prev & J_RIGHT))
        {
            game.cursor_direction = (game.cursor_direction + 1) % 4;
            menu_show_orientation_selection();
        }
        if (keys & J_A && !(keys_prev & J_A))
        {
            game.menu_state = MENU_NONE;
            menu_clear();
            HIDE_WIN;
            viewport_rebuild();
        }
        if (keys & J_B && !(keys_prev & J_B))
        {
            menu_show_tile_selection();
        }
    }
}
