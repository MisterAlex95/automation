#include "camera.h"
#include "constants.h"
#include "graphics.h"

camera_t camera = {0, 0};

void camera_init(void)
{
    camera.x = 0;
    camera.y = 0;
    move_bkg(camera.x, camera.y);
}

void camera_update(int dx, int dy)
{
    int new_camera_x = camera.x + dx * TILE_SIZE;
    int new_camera_y = camera.y + dy * TILE_SIZE;

    if (new_camera_x < 0)
        new_camera_x = 0;
    if (new_camera_y < 0)
        new_camera_y = 0;

    if (new_camera_x > (MAP_WIDTH_PIXEL - SCREEN_WIDTH))
        new_camera_x = MAP_WIDTH_PIXEL - SCREEN_WIDTH;
    if (new_camera_y > (MAP_HEIGHT_PIXEL - SCREEN_HEIGHT))
        new_camera_y = MAP_HEIGHT_PIXEL - SCREEN_HEIGHT;

    camera.x = new_camera_x;
    camera.y = new_camera_y;

    move_bkg(camera.x, camera.y);
}

UINT16 camera_get_x(void)
{
    return camera.x;
}

UINT16 camera_get_y(void)
{
    return camera.y;
}

UBYTE camera_can_move_left(void)
{
    return camera.x > 0;
}

UBYTE camera_can_move_right(void)
{
    return camera.x < (MAP_WIDTH_PIXEL - SCREEN_WIDTH);
}

UBYTE camera_can_move_up(void)
{
    return camera.y > 0;
}

UBYTE camera_can_move_down(void)
{
    return camera.y < (MAP_HEIGHT_PIXEL - SCREEN_HEIGHT);
}

// Coordinate system utilities
UINT16 world_to_screen_x(UINT16 world_x)
{
    return world_x - camera.x;
}

UINT16 world_to_screen_y(UINT16 world_y)
{
    return world_y - camera.y;
}

UINT16 screen_to_world_x(UINT16 screen_x)
{
    return screen_x + camera.x;
}

UINT16 screen_to_world_y(UINT16 screen_y)
{
    return screen_y + camera.y;
}

UINT8 world_to_tile_x(UINT16 world_x)
{
    return world_x / TILE_SIZE;
}

UINT8 world_to_tile_y(UINT16 world_y)
{
    return world_y / TILE_SIZE;
}

UINT16 tile_to_world_x(UINT8 tile_x)
{
    return tile_x * TILE_SIZE;
}

UINT16 tile_to_world_y(UINT8 tile_y)
{
    return tile_y * TILE_SIZE;
}

void entity_update_screen_position(UINT16 world_x, UINT16 world_y, UBYTE sprite_id)
{
    UINT16 screen_x = world_to_screen_x(world_x);
    UINT16 screen_y = world_to_screen_y(world_y);
    graphics_move_sprite(sprite_id, screen_x, screen_y);
}

void entity_set_world_position(UINT16 *world_x, UINT16 *world_y, UINT8 tile_x, UINT8 tile_y)
{
    *world_x = tile_to_world_x(tile_x);
    *world_y = tile_to_world_y(tile_y);
}

void camera_update_all_entity_positions(void)
{
    // TODO
}