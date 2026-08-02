#include "miner_system.h"
#include "item_system.h"
#include "../world/game_map.h"
#include "constants.h"

UBYTE miner_register(UBYTE tile_x, UBYTE tile_y, UBYTE direction)
{
    miner_t *miners = get_miners();

    if (game.miner_count >= MAX_MINERS)
        return FALSE;

    for (UBYTE i = 0; i < MAX_MINERS; i++)
    {
        if (miners[i].active)
            continue;

        miners[i].active = 1;
        miners[i].tile_x = tile_x;
        miners[i].tile_y = tile_y;
        miners[i].direction = direction;
        miners[i].rate = MINER_DEFAULT_RATE;
        miners[i].cooldown = MINER_DEFAULT_COOLDOWN;
        game.miner_count++;
        return TRUE;
    }
    return FALSE;
}

UBYTE miner_unregister(UBYTE tile_x, UBYTE tile_y)
{
    miner_t *miners = get_miners();

    for (UBYTE i = 0; i < MAX_MINERS; i++)
    {
        if (!miners[i].active)
            continue;
        if (miners[i].tile_x != tile_x || miners[i].tile_y != tile_y)
            continue;

        miners[i].active = 0;
        if (game.miner_count > 0)
            game.miner_count--;
        return TRUE;
    }
    return FALSE;
}

void miner_update_all(void)
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
        miner_spawn_item(&miners[i]);
    }
}

void miner_spawn_item(miner_t *miner)
{
    UBYTE spawn_x = miner->tile_x;
    UBYTE spawn_y = miner->tile_y;

    switch (miner->direction)
    {
    case DIRECTION_RIGHT:
        spawn_x += 1;
        break;
    case DIRECTION_LEFT:
        if (spawn_x > 0)
            spawn_x -= 1;
        break;
    case DIRECTION_UP:
        if (spawn_y > 0)
            spawn_y -= 1;
        break;
    case DIRECTION_DOWN:
        spawn_y += 1;
        break;
    }

    if (spawn_x >= MAP_WIDTH || spawn_y >= MAP_HEIGHT)
        return;

    if (!game_map_has_item_on_tile(spawn_x, spawn_y))
    {
        // Alternate ore/ingot for variety
        UBYTE type = ((miner->tile_x + miner->tile_y) & 1) ? ITEM_TYPE_ORE : ITEM_TYPE_INGOT;
        item_spawn(type, spawn_x, spawn_y, miner->direction);
    }
}
