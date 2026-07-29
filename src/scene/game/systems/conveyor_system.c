#include "conveyor_system.h"
#include "../entities/item_system.h"
#include "../world/game_map.h"
#include "map.h"
#include "constants.h"
#include "camera.h"
#include "game.h"

static UBYTE conveyor_frame = 0;
static UBYTE splitter_toggle = 0;

static UBYTE is_conveyor_tile(UBYTE tile)
{
    return tile == BG_CONVEYOR_BELT_RIGHT || tile == BG_CONVEYOR_BELT_LEFT ||
           tile == BG_CONVEYOR_BELT_UP || tile == BG_CONVEYOR_BELT_DOWN;
}

static void apply_direction(item_t *item, UBYTE direction, int *dx, int *dy)
{
    *dx = 0;
    *dy = 0;
    item->direction = direction;
    switch (direction)
    {
    case DIRECTION_RIGHT:
        *dx = 1;
        break;
    case DIRECTION_LEFT:
        *dx = -1;
        break;
    case DIRECTION_UP:
        *dy = -1;
        break;
    case DIRECTION_DOWN:
        *dy = 1;
        break;
    }
}

void conveyor_update_all_items(void)
{
    conveyor_frame++;
    if ((conveyor_frame % CONVEYOR_UPDATE_DIVISOR) != 0)
        return;

    UBYTE *activeItemsIds = game_get_active_items();

    for (UBYTE i = 0; activeItemsIds[i] < 0xFF; i++)
    {
        item_t *item = &game.items[activeItemsIds[i]];
        if (item->type == ITEM_TYPE_NONE)
            continue;

        conveyor_move_item(item);
    }
}

void conveyor_move_item(item_t *item)
{
    UBYTE tile_x = world_to_tile_x(item->world_x);
    UBYTE tile_y = world_to_tile_y(item->world_y);
    UBYTE tile_type = game_map_get_tile(tile_x, tile_y);

    int dx = 0, dy = 0;

    if (tile_type == BG_SPLITTER)
    {
        UBYTE turn = splitter_toggle & 1;
        splitter_toggle++;
        if (item->direction == DIRECTION_UP || item->direction == DIRECTION_DOWN)
            apply_direction(item, turn ? DIRECTION_LEFT : DIRECTION_RIGHT, &dx, &dy);
        else
            apply_direction(item, turn ? DIRECTION_UP : DIRECTION_DOWN, &dx, &dy);
    }
    else if (tile_type == BG_CONVEYOR_BELT_RIGHT)
        apply_direction(item, DIRECTION_RIGHT, &dx, &dy);
    else if (tile_type == BG_CONVEYOR_BELT_LEFT)
        apply_direction(item, DIRECTION_LEFT, &dx, &dy);
    else if (tile_type == BG_CONVEYOR_BELT_UP)
        apply_direction(item, DIRECTION_UP, &dx, &dy);
    else if (tile_type == BG_CONVEYOR_BELT_DOWN)
        apply_direction(item, DIRECTION_DOWN, &dx, &dy);
    else
        return;

    UINT16 new_x = item->world_x + dx;
    UINT16 new_y = item->world_y + dy;

    if (new_x >= MAP_WIDTH_PIXEL || new_y >= MAP_HEIGHT_PIXEL)
        return;

    if ((new_x % TILE_SIZE == 0) && (new_y % TILE_SIZE == 0))
    {
        UBYTE new_tile_x = (UBYTE)(new_x / TILE_SIZE);
        UBYTE new_tile_y = (UBYTE)(new_y / TILE_SIZE);

        if (game_map_has_item_on_tile(new_tile_x, new_tile_y))
            return;

        UBYTE dest = game_map_get_tile(new_tile_x, new_tile_y);
        if (!is_conveyor_tile(dest) && dest != BG_CHEST && dest != BG_SPLITTER)
            return;

        item->world_x = new_x;
        item->world_y = new_y;
    }
    else
    {
        item->world_x = new_x;
        item->world_y = new_y;
    }
}
