#include "cursor_camera_controller.h"
#include "camera.h"
#include "constants.h"

void cursor_camera_handle_movement(int dx, int dy, UINT8 *cursor_x, UINT8 *cursor_y)
{
    if (dx != 0)
    {
        int new_x = *cursor_x + dx;

        if (new_x < CAMERA_DEAD_ZONE_X_START && camera_can_move_left())
        {
            camera_update(dx, 0);
        }
        else if (new_x > CAMERA_DEAD_ZONE_X_END && camera_can_move_right())
        {
            camera_update(dx, 0);
        }
        else
        {
            *cursor_x = new_x;
        }
    }

    if (dy != 0)
    {
        int new_y = *cursor_y + dy;

        if (new_y < CAMERA_DEAD_ZONE_Y_START && camera_can_move_up())
        {
            camera_update(0, dy);
        }
        else if (new_y > CAMERA_DEAD_ZONE_Y_END && camera_can_move_down())
        {
            camera_update(0, dy);
        }
        else
        {
            *cursor_y = new_y;
        }
    }
}

void cursor_camera_center_cursor(UINT8 *cursor_x, UINT8 *cursor_y)
{
    *cursor_x = SCREEN_TILE_WIDTH / 2;
    *cursor_y = SCREEN_TILE_HEIGHT / 2;
}
