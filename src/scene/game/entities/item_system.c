#include "item_system.h"
#include "graphics.h"
#include "map.h"
#include "item.h"
#include "../world/game_map.h"
#include "camera.h"
#include "vram_layout.h"
#include "constants.h"

item_t *item_spawn(UBYTE type, UINT8 x, UINT8 y, UBYTE direction)
{
    if (x >= MAP_WIDTH || y >= MAP_HEIGHT)
        return NULL;

    if (game_map_has_item_on_tile(x, y))
        return NULL;

    item_t *item = item_get_free_slot();
    if (!item)
        return NULL;

    item->type = type;
    entity_set_world_position(&item->world_x, &item->world_y, x, y);
    item->direction = direction;
    item->sprite_id = item->id + 1; // 0 is reserved for cursor

    UINT8 tile_index = (type == ITEM_TYPE_ORE) ? (UINT8)ITEM_ORE_TILE : (UINT8)ITEM_INGOT_TILE;

    graphics_assign_sprite(item->sprite_id, tile_index);
    entity_update_screen_position(item->world_x, item->world_y, item->sprite_id);

    game_update_list_of_active_items();
    return item;
}

item_t *item_get_free_slot(void)
{
    for (UBYTE i = 0; i < MAX_ITEMS; i++)
    {
        if (game.items[i].type == ITEM_TYPE_NONE)
        {
            return &game.items[i];
        }
    }
    return NULL;
}

void item_destroy(item_t *item)
{
    if (!item)
        return;

    graphics_hide_sprite(item->sprite_id);
    item->type = ITEM_TYPE_NONE;
    game_update_list_of_active_items();
}

void item_update_movement(item_t *item)
{
    if (!item || item->type == ITEM_TYPE_NONE)
        return;
}
