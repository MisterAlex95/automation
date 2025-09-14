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
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        item_t *item = &game.items[i];
        if (item->type != ITEM_TYPE_NONE)
        {
            UBYTE tile = game_get_tile_at_position(item->pos_x, item->pos_y);
            switch (tile)
            {
            case BG_CONVEYOR_BELT_RIGHT:
                if (item->pos_x < (MAP_WIDTH * TILE_SIZE) - 1)
                    item->pos_x++;
                break;

            case BG_CONVEYOR_BELT_CORNER_RIGHT_DOWN:
                // move right until the end of the tile, then down
                if ((item->pos_x + 1) % TILE_SIZE != 0)
                {
                    if (item->pos_x < (MAP_WIDTH * TILE_SIZE) - 1)
                        item->pos_x++;
                }
                else if (item->pos_y < (MAP_HEIGHT * TILE_SIZE) - 1)
                    item->pos_y++;
                break;

            case BG_CONVEYOR_BELT_LEFT:
                if (item->pos_x > 0)
                    item->pos_x--;
                break;

            case BG_CONVEYOR_BELT_CORNER_DOWN_LEFT:
                // move down until the end of the tile, then left
                if ((item->pos_y + 1) % TILE_SIZE != 0)
                {
                    if (item->pos_y < (MAP_HEIGHT * TILE_SIZE) - 1)
                        item->pos_y++;
                }
                else if (item->pos_x > 0)
                    item->pos_x--;
                break;

            case BG_CONVEYOR_BELT_UP:
                if (item->pos_y > 0)
                    item->pos_y--;
                break;

            case BG_CONVEYOR_BELT_CORNER_LEFT_UP:
                // move left until the end of the tile, then up
                if ((item->pos_x) % TILE_SIZE != 0)
                {
                    if (item->pos_x > 0)
                        item->pos_x--;
                }
                else if (item->pos_y > 0)
                    item->pos_y--;
                break;

            case BG_CONVEYOR_BELT_DOWN:
                if (item->pos_y < (MAP_HEIGHT * TILE_SIZE) - 1)
                    item->pos_y++;
                break;

            case BG_CONVEYOR_BELT_CORNER_UP_RIGHT:
                // move up until the end of the tile, then right
                if ((item->pos_y) % TILE_SIZE != 0)
                {
                    if (item->pos_y > 0)
                        item->pos_y--;
                }
                else if (item->pos_x < (MAP_WIDTH * TILE_SIZE) - 1)
                    item->pos_x++;
                break;

            default:
                break;
            }
        }
    }
}

UBYTE game_get_tile_at_position(UINT8 x, UINT8 y)
{
    return mapBackground[x / TILE_SIZE + (y / TILE_SIZE) * MAP_WIDTH];
}