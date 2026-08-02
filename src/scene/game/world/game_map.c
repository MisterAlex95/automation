#include "game_map.h"
#include "chunk_system.h"
#include "viewport.h"
#include "map.h"
#include "game.h"
#include "camera.h"
#include "vram_layout.h"

UBYTE game_map_get_tile(UBYTE world_tx, UBYTE world_ty)
{
  return chunk_get_tile(world_tx, world_ty);
}

void game_map_set_tile(UBYTE world_tx, UBYTE world_ty, UBYTE tile_value)
{
  chunk_set_tile(world_tx, world_ty, tile_value);
  viewport_patch_tile(world_tx, world_ty);
}

UBYTE game_map_get_tile_at_position(UBYTE world_px, UBYTE world_py)
{
  return chunk_get_tile(world_to_tile_x(world_px), world_to_tile_y(world_py));
}

UBYTE game_map_count_items_on_tile(UBYTE world_tx, UBYTE world_ty)
{
  UBYTE count = 0;
  UBYTE *active = game_get_active_items();
  for (UBYTE i = 0; active[i] < 0xFF; i++)
  {
    item_t *item = &game.items[active[i]];
    if (item->type == ITEM_TYPE_NONE)
      continue;
    if (world_to_tile_x(item->world_x) == world_tx &&
        world_to_tile_y(item->world_y) == world_ty)
      count++;
  }
  return count;
}

UBYTE game_map_has_item_on_tile(UBYTE world_tx, UBYTE world_ty)
{
  return game_map_count_items_on_tile(world_tx, world_ty) > 0;
}

static UBYTE tile_is_empty(UBYTE tile)
{
  // BG_EMPTY is 128+. 0/font-range values mean uninitialized SRAM / wiped tilemap.
  return tile == BG_EMPTY || tile < TILE_FACTORY_START;
}

static UBYTE conveyor_tile_for_direction(UBYTE direction)
{
  if (direction == DIRECTION_UP)
    return BG_CONVEYOR_BELT_UP;
  if (direction == DIRECTION_DOWN)
    return BG_CONVEYOR_BELT_DOWN;
  if (direction == DIRECTION_LEFT)
    return BG_CONVEYOR_BELT_LEFT;
  return BG_CONVEYOR_BELT_RIGHT;
}

UBYTE game_map_place_tile(UBYTE world_tx, UBYTE world_ty, UBYTE tile_type,
                          UBYTE direction)
{
  if (world_tx >= MAP_WIDTH || world_ty >= MAP_HEIGHT)
    return FALSE;

  UBYTE current = chunk_get_tile(world_tx, world_ty);

  switch (tile_type)
  {
  case TILE_TYPE_NONE:
    if (current == BG_MINE || current == BG_WALL)
      return FALSE;
    if (tile_is_empty(current))
      return FALSE;
    game_map_set_tile(world_tx, world_ty, BG_EMPTY);
    return TRUE;

  case TILE_TYPE_WALL:
    if (!tile_is_empty(current))
      return FALSE;
    game_map_set_tile(world_tx, world_ty, BG_WALL);
    return TRUE;

  case TILE_TYPE_CONVEYOR:
    if (!tile_is_empty(current))
      return FALSE;
    game_map_set_tile(world_tx, world_ty, conveyor_tile_for_direction(direction));
    return TRUE;

  case TILE_TYPE_SPLITTER:
    if (!tile_is_empty(current))
      return FALSE;
    game_map_set_tile(world_tx, world_ty, BG_SPLITTER);
    return TRUE;

  case TILE_TYPE_MINER:
    if (current != BG_MINE)
      return FALSE;
    game_map_set_tile(world_tx, world_ty, BG_MINER);
    return TRUE;

  case TILE_TYPE_CHEST:
    if (!tile_is_empty(current))
      return FALSE;
    game_map_set_tile(world_tx, world_ty, BG_CHEST);
    return TRUE;

  default:
    return FALSE;
  }
}

void game_map_remove_tile(UBYTE world_tx, UBYTE world_ty)
{
  if (world_tx >= MAP_WIDTH || world_ty >= MAP_HEIGHT)
    return;
  game_map_set_tile(world_tx, world_ty, BG_EMPTY);
}
