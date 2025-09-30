#include "game_cursor.h"
#include "cursor_camera_controller.h"
#include "constants.h"
#include "camera.h"

void game_move_cursor(int dx, int dy)
{
    int new_x = game.cursor_x + dx;
    int new_y = game.cursor_y + dy;

    if (new_x < SCREEN_X_OFFSET)
        new_x = SCREEN_X_OFFSET;
    if (new_y < SCREEN_Y_OFFSET)
        new_y = SCREEN_Y_OFFSET;
    if (new_x > MAP_WIDTH - 1)
        new_x = MAP_WIDTH - 1;
    if (new_y > MAP_HEIGHT - 1)
        new_y = MAP_HEIGHT - 1;

    cursor_camera_handle_movement(dx, dy, &game.cursor_x, &game.cursor_y);
    
    if (game.cursor_x < SCREEN_X_OFFSET)
        game.cursor_x = SCREEN_X_OFFSET;
    if (game.cursor_y < SCREEN_Y_OFFSET)
        game.cursor_y = SCREEN_Y_OFFSET;
    if (game.cursor_x >= SCREEN_TILE_WIDTH)
        game.cursor_x = SCREEN_TILE_WIDTH - 1;
    if (game.cursor_y >= SCREEN_TILE_HEIGHT)
        game.cursor_y = SCREEN_TILE_HEIGHT - 1;
}

void game_display_cursor(void)
{
    UINT8 sprite_x = game.cursor_x * TILE_SIZE;
    UINT8 sprite_y = game.cursor_y * TILE_SIZE;
    graphics_move_sprite(UI_SPRITE_CURSOR, sprite_x, sprite_y);
}

void game_center_cursor(void)
{
    cursor_camera_center_cursor(&game.cursor_x, &game.cursor_y);
}

UINT8 game_get_cursor_x(void)
{
    return game.cursor_x;
}

UINT8 game_get_cursor_y(void)
{
    return game.cursor_y;
}