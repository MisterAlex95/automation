#include "game_map.h"
#include "map.h"
#include "game.h"
#include "graphics.h"

UBYTE tile_buffer[MAP_WIDTH][MAP_HEIGHT][MAX_ITEMS_PER_TILE] = {{{0}}};
UBYTE tile_count[MAP_WIDTH][MAP_HEIGHT] = {{0}};

UBYTE game_map_get_tile_at_position(UBYTE x, UBYTE y)
{
    return mapBackground[x / TILE_SIZE + (y / TILE_SIZE) * MAP_WIDTH];
}

UBYTE *game_map_get_items_on_tile(UBYTE tile_x, UBYTE tile_y, UBYTE *out_count)
{
    if (out_count)
        *out_count = tile_count[tile_x][tile_y];
    return tile_buffer[tile_x][tile_y];
}

void game_map_place_item_on_tile(UBYTE item_id, UBYTE tile_x, UBYTE tile_y)
{
    if (tile_count[tile_x][tile_y] < MAX_ITEMS_PER_TILE)
    {
        tile_buffer[tile_x][tile_y][tile_count[tile_x][tile_y]++] = item_id;
    }
}

void game_map_remove_item_from_tile(UBYTE item_id, UBYTE tile_x, UBYTE tile_y)
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

void game_map_clear_tile(UBYTE tile_x, UBYTE tile_y)
{
    tile_count[tile_x][tile_y] = 0;
    tile_buffer[tile_x][tile_y][0] = 0xFF;
}

void game_map_place_tile(UBYTE tile_x, UBYTE tile_y, UBYTE tile_type, UBYTE direction)
{
    UBYTE x = tile_x - 1, y = tile_y - 2;
    if (x >= MAP_WIDTH || y >= MAP_HEIGHT)
        return;

    UBYTE tile_index = x + (y * MAP_WIDTH);

    switch (tile_type)
    {
    case TILE_TYPE_NONE:
        mapBackground[tile_index] = BG_EMPTY;
        break;
    case TILE_TYPE_WALL:
        if (mapBackground[tile_index] != BG_EMPTY)
            break;
        mapBackground[tile_index] = BG_WALL;
        break;
    case TILE_TYPE_CONVEYOR:
        if (mapBackground[tile_index] != BG_EMPTY)
            break;

        if (direction == DIRECTION_UP)
            mapBackground[tile_index] = BG_CONVEYOR_BELT_UP;
        else if (direction == DIRECTION_DOWN)
            mapBackground[tile_index] = BG_CONVEYOR_BELT_DOWN;
        else if (direction == DIRECTION_LEFT)
            mapBackground[tile_index] = BG_CONVEYOR_BELT_LEFT;
        else
            mapBackground[tile_index] = BG_CONVEYOR_BELT_RIGHT;
        break;
    case TILE_TYPE_MINER:
        if (mapBackground[tile_index] == BG_MINE)
        {
            mapBackground[tile_index] = BG_MINER;
            miner_t *m = get_miners();
            m[game.miner_count].active = 1;
            m[game.miner_count].tile_x = tile_x;
            m[game.miner_count].tile_y = tile_y;
            m[game.miner_count].direction = direction;
            m[game.miner_count].rate = 200;
            m[game.miner_count].cooldown = 0;
            game.miner_count = (game.miner_count + 1) % MAX_MINERS;
        }
        break;
    case TILE_TYPE_CHEST:
        if (mapBackground[tile_index] != BG_EMPTY)
            break;
        mapBackground[tile_index] = BG_CHEST;
        break;
    default:
        break;
    }

    graphics_draw_background(mapBackground, MAP_WIDTH, MAP_HEIGHT);
}