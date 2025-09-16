#include "input_handler.h"
#include "game_cursor.h"
#include "game_logic.h"
#include "graphics.h"
#include "game.h"
#include "menu.h"
#include "map.h"

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
        game_spawn_tile(game.selected_tile, game_get_cursor_x(), game_get_cursor_y());
    }
    else if (keys & J_B && !(keys_prev & J_B))
    {
        game.cursor_direction = (game.cursor_direction + 1) % 4;
    }
    else if (keys & J_START && !(keys_prev & J_START))
    {
        game.paused = !game.paused;
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
                game.selected_tile = (game.selected_tile - 1) % SPRITE_VRAM_INDEX_TOTAL;
            menu_show_tile_selection();
        }
        if (keys & J_DOWN && !(keys_prev & J_DOWN))
        {
            game.selected_tile = (game.selected_tile + 1) % SPRITE_VRAM_INDEX_TOTAL;
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
            graphics_draw_background(mapBackground, MAP_WIDTH, MAP_HEIGHT);
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
            graphics_draw_background(mapBackground, MAP_WIDTH, MAP_HEIGHT);
        }
        if (keys & J_B && !(keys_prev & J_B))
        {
            menu_show_tile_selection();
        }
    }
}
