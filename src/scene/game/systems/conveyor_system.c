#include "conveyor_system.h"
#include "../entities/item_system.h"
#include "../world/game_map.h"
#include "map.h"

void conveyor_update_all_items(void)
{
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
    UBYTE item_x_pos = item->pos_x - DEVICE_SPRITE_PX_OFFSET_X +
                       (item->direction == DIRECTION_RIGHT ? 0 : TILE_SIZE - 1);
    UBYTE item_y_pos = item->pos_y - DEVICE_SPRITE_PX_OFFSET_Y +
                       (item->direction == DIRECTION_DOWN ? 0 : TILE_SIZE - 1);

    UBYTE tile_type = game_map_get_tile_at_position(item_x_pos, item_y_pos);

    int dx = 0, dy = 0;

    switch (tile_type)
    {
    case BG_CONVEYOR_BELT_RIGHT:
        dx = +1;
        item->direction = DIRECTION_RIGHT;
        break;
    case BG_CONVEYOR_BELT_LEFT:
        dx = -1;
        item->direction = DIRECTION_LEFT;
        break;
    case BG_CONVEYOR_BELT_UP:
        dy = -1;
        item->direction = DIRECTION_UP;
        break;
    case BG_CONVEYOR_BELT_DOWN:
        dy = +1;
        item->direction = DIRECTION_DOWN;
        break;
    default:
    {
        UBYTE new_tile_x = (item->pos_x + 1) / TILE_SIZE;
        UBYTE new_tile_y = (item->pos_y + 1) / TILE_SIZE;

        UBYTE item_count;
        game_map_get_items_on_tile(new_tile_x, new_tile_y, &item_count);

        if (item_count > 0)
        {
            return;
        }
        return;
    }
    }

    UBYTE new_x = item->pos_x + dx;
    UBYTE new_y = item->pos_y + dy;

    if ((new_x % TILE_SIZE == 0) && (new_y % TILE_SIZE == 0))
    {
        UBYTE new_tile_x = new_x / TILE_SIZE;
        UBYTE new_tile_y = new_y / TILE_SIZE;

        UBYTE item_count;
        game_map_get_items_on_tile(new_tile_x, new_tile_y, &item_count);

        if (item_count > 0)
        {
            return;
        }

        game_map_remove_item_from_tile(item->id, item->pos_x / TILE_SIZE, item->pos_y / TILE_SIZE);
        item->pos_x = new_x;
        item->pos_y = new_y;
        game_map_place_item_on_tile(item->id, new_tile_x, new_tile_y);
    }
    else
    {
        item->pos_x = new_x;
        item->pos_y = new_y;
    }
}
