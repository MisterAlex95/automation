#include "chest_system.h"
#include "../entities/item_system.h"
#include "../world/game_map.h"
#include "map.h"

void chest_update_all_items(void)
{
    UBYTE *activeItemsIds = game_get_active_items();

    for (UBYTE i = 0; activeItemsIds[i] < 0xFF; i++)
    {
        item_t *item = &game.items[activeItemsIds[i]];
        if (item->type == ITEM_TYPE_NONE)
            continue;

        chest_process_item(item);
    }
}

void chest_process_item(item_t *item)
{
    UBYTE item_x_pos = item->pos_x - DEVICE_SPRITE_PX_OFFSET_X +
                       (item->direction == DIRECTION_RIGHT ? 0 : TILE_SIZE - 1);
    UBYTE item_y_pos = item->pos_y - DEVICE_SPRITE_PX_OFFSET_Y +
                       (item->direction == DIRECTION_DOWN ? 0 : TILE_SIZE - 1);

    UBYTE tile_type = game_map_get_tile_at_position(item_x_pos, item_y_pos);

    if (tile_type != BG_CHEST)
        return;

    item_destroy(item);
}
