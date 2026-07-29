#include "save_system.h"
#include "sram_system.h"
#include "game.h"
#include "../world/chunk_system.h"
#include "../entities/item_system.h"
#include "constants.h"
#include "graphics.h"
#include "item.h"

UBYTE save_exists(void)
{
  return world_sram_is_valid() && sram_read_byte(SRAM_HEADER_ADDR + 3) == 1;
}

static void save_miners(void)
{
  miner_t *miners = get_miners();
  sram_write_byte(SRAM_MINERS_ADDR, game.miner_count);
  for (UBYTE i = 0; i < MAX_MINERS; i++)
  {
    UINT16 base = SRAM_MINERS_ADDR + 1 + (UINT16)i * 6;
    sram_write_byte(base + 0, miners[i].active);
    sram_write_byte(base + 1, miners[i].tile_x);
    sram_write_byte(base + 2, miners[i].tile_y);
    sram_write_byte(base + 3, miners[i].direction);
    sram_write_byte(base + 4, (UBYTE)(miners[i].rate & 0xFF));
    sram_write_byte(base + 5, (UBYTE)((miners[i].rate >> 8) & 0xFF));
  }
}

static void load_miners(void)
{
  miner_t *miners = get_miners();
  game.miner_count = sram_read_byte(SRAM_MINERS_ADDR);
  for (UBYTE i = 0; i < MAX_MINERS; i++)
  {
    UINT16 base = SRAM_MINERS_ADDR + 1 + (UINT16)i * 6;
    miners[i].active = sram_read_byte(base + 0);
    miners[i].tile_x = sram_read_byte(base + 1);
    miners[i].tile_y = sram_read_byte(base + 2);
    miners[i].direction = sram_read_byte(base + 3);
    miners[i].rate = sram_read_byte(base + 4) | ((UINT16)sram_read_byte(base + 5) << 8);
    miners[i].cooldown = 0;
  }
}

static void save_items(void)
{
  UBYTE count = 0;
  for (UBYTE i = 0; i < MAX_ITEMS; i++)
  {
    if (game.items[i].type == ITEM_TYPE_NONE)
      continue;
    UINT16 base = SRAM_ITEMS_ADDR + 1 + (UINT16)count * 6;
    sram_write_byte(base + 0, game.items[i].type);
    sram_write_byte(base + 1, game.items[i].direction);
    sram_write_byte(base + 2, (UBYTE)(game.items[i].world_x & 0xFF));
    sram_write_byte(base + 3, (UBYTE)((game.items[i].world_x >> 8) & 0xFF));
    sram_write_byte(base + 4, (UBYTE)(game.items[i].world_y & 0xFF));
    sram_write_byte(base + 5, (UBYTE)((game.items[i].world_y >> 8) & 0xFF));
    count++;
    if (count >= 20)
      break; // keep save block bounded
  }
  sram_write_byte(SRAM_ITEMS_ADDR, count);
}

static void load_items(void)
{
  for (UBYTE i = 0; i < MAX_ITEMS; i++)
  {
    game.items[i].type = ITEM_TYPE_NONE;
    graphics_hide_sprite(game.items[i].sprite_id);
  }

  UBYTE count = sram_read_byte(SRAM_ITEMS_ADDR);
  if (count > 20)
    count = 20;

  for (UBYTE i = 0; i < count; i++)
  {
    UINT16 base = SRAM_ITEMS_ADDR + 1 + (UINT16)i * 6;
    UBYTE type = sram_read_byte(base + 0);
    UBYTE dir = sram_read_byte(base + 1);
    UINT16 wx = sram_read_byte(base + 2) | ((UINT16)sram_read_byte(base + 3) << 8);
    UINT16 wy = sram_read_byte(base + 4) | ((UINT16)sram_read_byte(base + 5) << 8);
    item_t *item = item_get_free_slot();
    if (!item)
      break;
    item->type = type;
    item->direction = dir;
    item->world_x = wx;
    item->world_y = wy;
    item->sprite_id = item->id + 1;
    {
      UINT8 tile_index = (type == ITEM_TYPE_ORE) ? (UINT8)ITEM_ORE_TILE : (UINT8)ITEM_INGOT_TILE;
      graphics_assign_sprite(item->sprite_id, tile_index);
    }
  }
  game_update_list_of_active_items();
}

void save_game(void)
{
  chunk_flush_all();
  world_sram_write_header();
  sram_write_byte(SRAM_SCORE_ADDR, (UBYTE)(game.score & 0xFF));
  sram_write_byte(SRAM_SCORE_ADDR + 1, (UBYTE)((game.score >> 8) & 0xFF));
  save_miners();
  save_items();
}

void load_game(void)
{
  game_init();
  world_init(FALSE);
  game.score = sram_read_byte(SRAM_SCORE_ADDR) | ((UINT16)sram_read_byte(SRAM_SCORE_ADDR + 1) << 8);
  game.won = (game.score >= WIN_SCORE);
  load_miners();
  load_items();
}

void save_new_game(void)
{
  game_init();
  world_init(TRUE);
  save_game();
}
