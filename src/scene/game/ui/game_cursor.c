#include "game_cursor.h"
#include "camera.h"
#include "constants.h"

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

    if (dx != 0)
    {
        int dead_start_x = CAMERA_DEAD_ZONE_X_START;
        int dead_end_x = CAMERA_DEAD_ZONE_X_END;

        if (new_x < dead_start_x && camera_x > 0)
        {
            camera_update(dx, 0);
        }
        else if (new_x > dead_end_x && camera_x < MAP_WIDTH_PIXEL - SCREEN_WIDTH)
        {
            camera_update(dx, 0);
        }
        else
        {
            game.cursor_x = new_x;
        }
    }

    if (dy != 0)
    {
        int dead_start_y = CAMERA_DEAD_ZONE_Y_START;
        int dead_end_y = CAMERA_DEAD_ZONE_Y_END;

        if (new_y < dead_start_y && camera_y > 0)
        {
            camera_update(0, dy);
        }
        else if (new_y > dead_end_y && camera_y < MAP_HEIGHT_PIXEL - SCREEN_HEIGHT)
        {
            camera_update(0, dy);
        }
        else
        {
            game.cursor_y = new_y;
        }
    }
}

void game_display_cursor(void)
{
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