#include "game_cursor.h"

void game_move_cursor(int dx, int dy)
{
    game.cursor_x += dx;
    game.cursor_y += dy;

    if (game.cursor_x < 1)
        game.cursor_x = 1;

    if (game.cursor_y < 2)
        game.cursor_y = 2;

    if (game.cursor_x >= MAP_WIDTH)
        game.cursor_x = MAP_WIDTH - 1;

    if (game.cursor_y >= MAP_HEIGHT)
        game.cursor_y = MAP_HEIGHT - 1;

    // Update cursor sprite position
    UINT8 sprite_x = game.cursor_x * TILE_SIZE;
    UINT8 sprite_y = game.cursor_y * TILE_SIZE;
    graphics_move_sprite(UI_SPRITE_CURSOR, sprite_x, sprite_y);
}

UINT8 game_get_cursor_x(void)
{
    return game.cursor_x;
}

UINT8 game_get_cursor_y(void)
{
    return game.cursor_y;
}