#include "game_map.h"
#include "map.h"
#include "game.h"

UBYTE game_get_tile_at_position(UBYTE x, UBYTE y)
{
    return mapBackground[x / TILE_SIZE + (y / TILE_SIZE) * MAP_WIDTH];
}

UBYTE *game_get_items_on_tile(UBYTE tile_x, UBYTE tile_y, UBYTE *out_count)
{
    if (out_count)
        *out_count = tile_count[tile_x][tile_y];
    return tile_buffer[tile_x][tile_y];
}

void game_place_item_on_tile(UBYTE item_id, UBYTE tile_x, UBYTE tile_y)
{
    if (tile_count[tile_x][tile_y] < MAX_ITEMS_PER_TILE)
    {
        tile_buffer[tile_x][tile_y][tile_count[tile_x][tile_y]++] = item_id;
    }
}

void game_remove_item_from_tile(UBYTE item_id, UBYTE tile_x, UBYTE tile_y)
{
    UBYTE *items = tile_buffer[tile_x][tile_y];
    UBYTE count = tile_count[tile_x][tile_y];

    for (UBYTE i = 0; i < count; i++)
    {
        if (items[i] == item_id)
        {
            items[i] = items[count - 1];
            tile_count[tile_x][tile_y]--;
            break;
        }
    }
}

void game_clear_tile(UBYTE tile_x, UBYTE tile_y)
{
    tile_count[tile_x][tile_y] = 0;
    tile_buffer[tile_x][tile_y][0] = 0xFF;
}