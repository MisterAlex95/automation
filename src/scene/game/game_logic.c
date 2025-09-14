#include "game_logic.h"
#include "scene_menu.h"
#include "map.h"
#include "item.h"
#include "graphics.h"
#include "timer.h"

void game_spawn_item(UBYTE type, UINT8 x, UINT8 y)
{
    item_t *item = game_get_free_item_slot();
    if (!item)
        return;

    item->type = type;
    item->pos_x = x * TILE_SIZE;
    item->pos_y = y * TILE_SIZE;
    item->sprite_id = item->id + ITEMS_VRAM_INDEX_TOTAL;

    graphics_assign_sprite(item->sprite_id, ITEMS_VRAM_INDEX_TOTAL);
    graphics_move_sprite(item->sprite_id, item->pos_x, item->pos_y);

    game_update_list_of_active_items();
}

item_t *game_get_free_item_slot(void)
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        if (game.items[i].type == ITEM_TYPE_NONE)
        {
            return &game.items[i];
        }
    }
    return NULL;
}

void game_conveyor_belt_update(void)
{
    UBYTE *activeItemsIds = game_get_active_items();
    for (int i = 0; activeItemsIds[i] < 0xFF; i++)
    {
        item_t *item = &game.items[activeItemsIds[i]];
        if (item->type == ITEM_TYPE_NONE)
            continue;

        UBYTE tile = game_get_tile_at_position(item->pos_x - START_X, item->pos_y - START_Y);

        int dx = 0, dy = 0;

        switch (tile)
        {
        case BG_CONVEYOR_BELT_RIGHT:
            dx = +1;
            break;
        case BG_CONVEYOR_BELT_LEFT:
            dx = -1;
            break;
        case BG_CONVEYOR_BELT_UP:
            dy = -1;
            break;
        case BG_CONVEYOR_BELT_DOWN:
            dy = +1;
            break;

        default:
            break;
        }

        int new_x = item->pos_x + dx;
        int new_y = item->pos_y + dy;

        if (new_x >= 0 && new_x < (MAP_WIDTH * TILE_SIZE))
            item->pos_x = new_x;
        if (new_y >= 0 && new_y < (MAP_HEIGHT * TILE_SIZE))
            item->pos_y = new_y;
    }
}

UBYTE game_get_tile_at_position(UINT8 x, UINT8 y)
{
    return mapBackground[x / TILE_SIZE + (y / TILE_SIZE) * MAP_WIDTH];
}