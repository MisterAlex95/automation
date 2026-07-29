#include "game_cursor.h"
#include "cursor_camera_controller.h"
#include "constants.h"
#include "camera.h"

void game_move_cursor(int dx, int dy)
{
    cursor_camera_handle_movement(dx, dy, &game.cursor_x, &game.cursor_y);

    if (game.cursor_x < SCREEN_X_OFFSET)
        game.cursor_x = SCREEN_X_OFFSET;
    if (game.cursor_y < SCREEN_Y_OFFSET)
        game.cursor_y = SCREEN_Y_OFFSET;
    if (game.cursor_x >= SCREEN_TILE_WIDTH)
        game.cursor_x = SCREEN_TILE_WIDTH - 1;
    if (game.cursor_y >= SCREEN_TILE_HEIGHT)
        game.cursor_y = SCREEN_TILE_HEIGHT - 1;

    // Clamp so world tile stays inside map
    UBYTE wx = cursor_screen_to_world_x(game.cursor_x);
    UBYTE wy = cursor_screen_to_world_y(game.cursor_y);
    if (wx >= MAP_WIDTH)
        game.cursor_x = SCREEN_X_OFFSET + (MAP_WIDTH - 1) - camera_get_tile_x();
    if (wy >= MAP_HEIGHT)
        game.cursor_y = SCREEN_Y_OFFSET + (MAP_HEIGHT - 1) - camera_get_tile_y();
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
