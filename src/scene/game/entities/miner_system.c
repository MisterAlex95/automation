#include "miner_system.h"
#include "item_system.h"
#include "../world/game_map.h"
#include "constants.h"

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
        item_spawn(ITEM_TYPE_INGOT, spawn_x, spawn_y, miner->direction);
    }
}
