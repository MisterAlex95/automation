#include "camera.h"
#include "graphics.h"
#include "game.h"
#include "../scene/game/world/viewport.h"
#include <gb/hardware.h>

camera_t camera = {0, 0};

void camera_init(void)
{
    camera.x = 0;
    camera.y = 0;
    move_bkg(0, 0);
}

void camera_update(int dx, int dy)
{
    int new_camera_x = (int)camera.x + dx * TILE_SIZE;
    int new_camera_y = (int)camera.y + dy * TILE_SIZE;

    if (new_camera_x < 0)
        new_camera_x = 0;
    if (new_camera_y < 0)
        new_camera_y = 0;

    if (new_camera_x > (MAP_WIDTH_PIXEL - SCREEN_WIDTH))
        new_camera_x = MAP_WIDTH_PIXEL - SCREEN_WIDTH;
    if (new_camera_y > (MAP_HEIGHT_PIXEL - SCREEN_HEIGHT))
        new_camera_y = MAP_HEIGHT_PIXEL - SCREEN_HEIGHT;

    if ((UINT16)new_camera_x == camera.x && (UINT16)new_camera_y == camera.y)
        return;

    INT8 dtx = (INT8)(((int)new_camera_x - (int)camera.x) / TILE_SIZE);
    INT8 dty = (INT8)(((int)new_camera_y - (int)camera.y) / TILE_SIZE);

    camera.x = (UINT16)new_camera_x;
    camera.y = (UINT16)new_camera_y;

    viewport_scroll(dtx, dty);
    camera_update_all_entity_positions();
}

UINT16 camera_get_x(void)
{
    return camera.x;
}

UINT16 camera_get_y(void)
{
    return camera.y;
}

UBYTE camera_get_tile_x(void)
{
    return (UBYTE)(camera.x / TILE_SIZE);
}

UBYTE camera_get_tile_y(void)
{
    return (UBYTE)(camera.y / TILE_SIZE);
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
    return (UINT8)(world_x / TILE_SIZE);
}

UINT8 world_to_tile_y(UINT16 world_y)
{
    return (UINT8)(world_y / TILE_SIZE);
}

UINT16 tile_to_world_x(UINT8 tile_x)
{
    return (UINT16)tile_x * TILE_SIZE;
}

UINT16 tile_to_world_y(UINT8 tile_y)
{
    return (UINT16)tile_y * TILE_SIZE;
}

UBYTE cursor_screen_to_world_x(UBYTE cursor_sx)
{
    return (UBYTE)(camera_get_tile_x() + cursor_sx - SCREEN_X_OFFSET);
}

UBYTE cursor_screen_to_world_y(UBYTE cursor_sy)
{
    return (UBYTE)(camera_get_tile_y() + cursor_sy - SCREEN_Y_OFFSET);
}

void entity_update_screen_position(UINT16 world_x, UINT16 world_y, UBYTE sprite_id)
{
    UINT16 screen_x = world_to_screen_x(world_x) + DEVICE_SPRITE_PX_OFFSET_X;
    UINT16 screen_y = world_to_screen_y(world_y) + DEVICE_SPRITE_PX_OFFSET_Y;
    graphics_move_sprite(sprite_id, (UINT8)screen_x, (UINT8)screen_y);
}

void entity_set_world_position(UINT16 *world_x, UINT16 *world_y, UINT8 tile_x, UINT8 tile_y)
{
    *world_x = tile_to_world_x(tile_x);
    *world_y = tile_to_world_y(tile_y);
}

void camera_update_all_entity_positions(void)
{
    UBYTE *active = game_get_active_items();
    for (UBYTE i = 0; active[i] < 0xFF; i++)
    {
        item_t *item = &game.items[active[i]];
        if (item->type != ITEM_TYPE_NONE)
            entity_update_screen_position(item->world_x, item->world_y, item->sprite_id);
    }
}
