#include "game_logic.h"
#include "map.h"
#include "../world/game_map.h"
#include "../entities/miner_system.h"
#include "../systems/conveyor_system.h"
#include "../systems/chest_system.h"

void game_spawn_tile(UBYTE type, UINT8 x, UINT8 y)
{
    UBYTE previous = game_map_get_tile(x, y);

    if (type == TILE_TYPE_MINER)
    {
        // Register first so a full miner list never leaves an orphan BG_MINER tile
        if (!miner_register(x, y, game.cursor_direction))
            return;
        if (!game_map_place_tile(x, y, type, game.cursor_direction))
        {
            miner_unregister(x, y);
            return;
        }
        return;
    }

    if (!game_map_place_tile(x, y, type, game.cursor_direction))
        return;

    if (type == TILE_TYPE_NONE && previous == BG_MINER)
        miner_unregister(x, y);
}

void game_conveyor_belt_update(void)
{
    conveyor_update_all_items();
}

void game_miners_update(void)
{
    miner_update_all();
}

void game_chest_update(void)
{
    chest_update_all_items();
}
