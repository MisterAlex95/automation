#include "game_logic.h"
#include "scene_menu.h"
#include "map.h"
#include "item.h"
#include "graphics.h"
#include "timer.h"
#include "../world/game_map.h"
#include "vram_layout.h"
#include "../entities/item_system.h"
#include "../entities/miner_system.h"
#include "../systems/conveyor_system.h"
#include "../systems/chest_system.h"

item_t *game_spawn_item(UBYTE type, UINT8 x, UINT8 y, UBYTE direction)
{
    return item_spawn(type, x, y, direction);
}

item_t *game_get_free_item_slot(void)
{
    return item_get_free_slot();
}

void game_spawn_tile(UBYTE type, UINT8 x, UINT8 y)
{
    if (type == TILE_TYPE_NONE)
        return;

    UBYTE placed = game_map_place_tile(x, y, type, game.cursor_direction);
    if (!placed)
        return;

    if (type == TILE_TYPE_MINER)
        miner_register(x, y, game.cursor_direction);
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
