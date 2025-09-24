#include "game_logic.h"
#include "scene_menu.h"
#include "map.h"
#include "item.h"
#include "graphics.h"
#include "timer.h"
#include "game_map.h"

// Item
item_t *game_spawn_item(UBYTE type, UINT8 x, UINT8 y, UBYTE direction)
{
    item_t *item = game_get_free_item_slot();
    if (!item)
        return NULL;

    item->type = type;
    item->pos_x = x * TILE_SIZE;
    item->pos_y = y * TILE_SIZE;
    item->direction = direction;
    item->sprite_id = item->id + ITEMS_VRAM_INDEX_TOTAL;

    game_map_place_item_on_tile(item->id, x, y);

    graphics_assign_sprite(item->sprite_id, ITEMS_VRAM_INDEX_TOTAL);
    graphics_move_sprite(item->sprite_id, item->pos_x, item->pos_y);

    game_update_list_of_active_items();
    return item;
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

void game_spawn_tile(UBYTE type, UINT8 x, UINT8 y)
{
    switch (type)
    {
    case TILE_TYPE_NONE:
        // game_map_place_tile(x, y, TILE_TYPE_NONE, 0);
        // Nothing to do.
        break;
    case TILE_TYPE_CONVEYOR:
        game_map_place_tile(x, y, TILE_TYPE_CONVEYOR, game.cursor_direction);
        break;
    case TILE_TYPE_MINER:
        game_map_place_tile(x, y, TILE_TYPE_MINER, game.cursor_direction);
        break;
    case TILE_TYPE_CHEST:
        game_map_place_tile(x, y, TILE_TYPE_CHEST, 0);
        break;
    default:
        break;
    }
}

void game_conveyor_belt_update(void)
{
    UBYTE *activeItemsIds = game_get_active_items();

    for (UBYTE i = 0; activeItemsIds[i] < 0xFF; i++)
    {
        item_t *item = &game.items[activeItemsIds[i]];
        if (item->type == ITEM_TYPE_NONE)
            continue;

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
                continue;
            }
            continue;
        }
        break;
        }

        UBYTE new_x = item->pos_x + dx;
        UBYTE new_y = item->pos_y + dy;

        if ((new_x % TILE_SIZE == 0) && (new_y % TILE_SIZE == 0))
        {
            UBYTE new_tile_x = new_x / TILE_SIZE;
            UBYTE new_tile_y = new_y / TILE_SIZE;

            UBYTE item_count;
            UBYTE *items_on_tile = game_map_get_items_on_tile(new_tile_x, new_tile_y, &item_count);

            if (item_count > 0)
            {
                continue;
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
}

void game_miners_update(void)
{
    miner_t *miners = get_miners();
    for (UBYTE i = 0; i < MAX_MINERS; i++)
    {
        if (miners[i].active != 1)
            continue;

        if (miners[i].rate == 0)
            continue;

        if (miners[i].cooldown > 0)
        {
            miners[i].cooldown--;
            continue;
        }

        miners[i].cooldown = miners[i].rate;

        UBYTE spawn_x = miners[i].tile_x;
        UBYTE spawn_y = miners[i].tile_y;

        switch (miners[i].direction)
        {
        case DIRECTION_RIGHT:
            spawn_x += 1;
            break;
        case DIRECTION_LEFT:
            spawn_x -= 1;
            break;
        case DIRECTION_UP:
            spawn_y -= 1;
            break;
        case DIRECTION_DOWN:
            spawn_y += 1;
            break;
        }

        UBYTE item_count;
        game_map_get_items_on_tile(spawn_x, spawn_y, &item_count);

        if (item_count == 0)
        {
            game_spawn_item(ITEM_TYPE_INGOT, spawn_x, spawn_y, miners[i].direction);
        }
    }
}

void game_chest_update(void)
{
    UBYTE *activeItemsIds = game_get_active_items();

    for (UBYTE i = 0; activeItemsIds[i] < 0xFF; i++)
    {
        item_t *item = &game.items[activeItemsIds[i]];
        if (item->type == ITEM_TYPE_NONE)
            continue;

        UBYTE item_x_pos = item->pos_x - DEVICE_SPRITE_PX_OFFSET_X +
                           (item->direction == DIRECTION_RIGHT ? 0 : TILE_SIZE - 1);
        UBYTE item_y_pos = item->pos_y - DEVICE_SPRITE_PX_OFFSET_Y +
                           (item->direction == DIRECTION_DOWN ? 0 : TILE_SIZE - 1);

        UBYTE tile_type = game_map_get_tile_at_position(item_x_pos, item_y_pos);

        if (tile_type != BG_CHEST)
            continue;

        game_map_remove_item_from_tile(item->id, item->pos_x / TILE_SIZE, item->pos_y / TILE_SIZE);

        graphics_hide_sprite(item->sprite_id);
        item->type = ITEM_TYPE_NONE;

        game_update_list_of_active_items();
    }
}