#include "game_logic.h"
#include "scene_menu.h"
#include "map.h"
#include "item.h"
#include "graphics.h"
#include "timer.h"
#include "game_map.h"

void game_spawn_item(UBYTE type, UINT8 x, UINT8 y)
{
    item_t *item = game_get_free_item_slot();
    if (!item)
        return;

    item->type = type;
    item->pos_x = x * TILE_SIZE;
    item->pos_y = y * TILE_SIZE;
    item->sprite_id = item->id + ITEMS_VRAM_INDEX_TOTAL;

    game_map_place_item_on_tile(item->id, item->pos_x / TILE_SIZE, item->pos_y / TILE_SIZE);

    graphics_assign_sprite(item->sprite_id, ITEMS_VRAM_INDEX_TOTAL);
    graphics_move_sprite(item->sprite_id, item->pos_x, item->pos_y);

    game_update_list_of_active_items();
}

void game_spawn_tile(UBYTE type, UINT8 x, UINT8 y)
{
    switch (type)
    {
    case TILE_TYPE_CONVEYOR:
        game_map_place_tile(x, y, TILE_TYPE_CONVEYOR, game.cursor_direction);
        break;
    default:
        break;
    }
}

item_t *game_get_free_item_slot(void)
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

void game_conveyor_belt_update(void)
{
    UBYTE *activeItemsIds = game_get_active_items();
    for (UBYTE i = 0; activeItemsIds[i] < 0xFF; i++)
    {
        item_t *item = &game.items[activeItemsIds[i]];
        if (item->type == ITEM_TYPE_NONE)
            continue;

        UBYTE item_x_pos = item->pos_x - DEVICE_SPRITE_PX_OFFSET_X + (item->direction == DIRECTION_RIGHT ? 0 : TILE_SIZE - 1);
        UBYTE item_y_pos = item->pos_y - DEVICE_SPRITE_PX_OFFSET_Y + (item->direction == DIRECTION_DOWN ? 0 : TILE_SIZE - 1);
        UBYTE tile = game_map_get_tile_at_position(item_x_pos, item_y_pos);

        int dx = 0, dy = 0;

        switch (tile)
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
            break;
        }

        UBYTE new_x = item->pos_x + dx;
        UBYTE new_y = item->pos_y + dy;

        game_map_remove_item_from_tile(item->id, item->pos_x / TILE_SIZE, item->pos_y / TILE_SIZE);
        if (new_x >= 0 && new_x < (MAP_WIDTH * TILE_SIZE))
            item->pos_x = new_x;
        if (new_y >= 0 && new_y < (MAP_HEIGHT * TILE_SIZE))
            item->pos_y = new_y;

        game_map_place_item_on_tile(item->id, item->pos_x / TILE_SIZE, item->pos_y / TILE_SIZE);
    }
}