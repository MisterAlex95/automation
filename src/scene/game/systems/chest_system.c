#include "chest_system.h"
#include "../entities/item_system.h"
#include "../world/game_map.h"
#include "map.h"
#include "camera.h"
#include "game.h"

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
    UBYTE tile_x = world_to_tile_x(item->world_x);
    UBYTE tile_y = world_to_tile_y(item->world_y);
    UBYTE tile_type = game_map_get_tile(tile_x, tile_y);

    if (tile_type != BG_CHEST)
        return;

    if (item->type == ITEM_TYPE_INGOT)
        game_add_score(1);
    else if (item->type == ITEM_TYPE_ORE)
        game_add_score(2);

    item_destroy(item);
}
