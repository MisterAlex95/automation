#include "chunk_system.h"
#include "../../../assets/map.h"
#include "../core/sram_system.h"
#include "camera.h"

static UBYTE loaded_chunk_count = 0;
static UINT16 lru_tick = 0;
static cached_chunk_t loaded_chunks[MAX_LOADED_CHUNKS];
// O(1) chunk_id -> slot index (0xFF = not loaded)
static UBYTE chunk_slot_by_id[SRAM_TOTAL_CHUNKS];

static UBYTE chunk_compute_checksum(const chunk_data_t *data)
{
  UBYTE sum = 0;
  const UBYTE *bytes = (const UBYTE *)data->tiles;
  for (UINT16 i = 0; i < (UINT16)(CHUNK_SIZE * CHUNK_SIZE); i++)
    sum ^= bytes[i];
  // Non-zero salt so an all-zero chunk never looks valid by accident
  return sum ^ 0xA7;
}

static void chunk_finalize_checksum(chunk_data_t *data)
{
  data->checksum = chunk_compute_checksum(data);
}

static UBYTE chunk_data_is_valid(const chunk_data_t *data)
{
  return data->checksum == chunk_compute_checksum(data);
}

static UBYTE tile_from_template(UBYTE wx, UBYTE wy)
{
  UBYTE tile = BG_EMPTY;

  if (wx < MAP_TEMPLATE_WIDTH && wy < MAP_TEMPLATE_HEIGHT)
    tile = mapTemplate[wx + wy * MAP_TEMPLATE_WIDTH];

  if (wx == 0 || wy == 0 || wx == MAP_WIDTH - 1 || wy == MAP_HEIGHT - 1)
    tile = BG_WALL;

  return tile;
}

static void fill_chunk_from_template(UBYTE chunk_id, chunk_data_t *out)
{
  UBYTE cx = chunk_id % CHUNK_COUNT_X;
  UBYTE cy = chunk_id / CHUNK_COUNT_X;

  for (UBYTE ly = 0; ly < CHUNK_SIZE; ly++)
  {
    for (UBYTE lx = 0; lx < CHUNK_SIZE; lx++)
    {
      UBYTE wx = cx * CHUNK_SIZE + lx;
      UBYTE wy = cy * CHUNK_SIZE + ly;
      out->tiles[ly][lx] = tile_from_template(wx, wy);
    }
  }
  chunk_finalize_checksum(out);
}

static void chunk_touch(cached_chunk_t *chunk)
{
  chunk->last_used = ++lru_tick;
}

static UBYTE chunk_intersects_camera(UBYTE chunk_id, UBYTE cam_tx, UBYTE cam_ty)
{
  UBYTE cx = chunk_id % CHUNK_COUNT_X;
  UBYTE cy = chunk_id / CHUNK_COUNT_X;
  UBYTE min_cx = cam_tx / CHUNK_SIZE;
  UBYTE min_cy = cam_ty / CHUNK_SIZE;
  UBYTE max_tx = cam_tx + SCREEN_TILE_WIDTH - 1;
  UBYTE max_ty = cam_ty + SCREEN_TILE_HEIGHT - 1;
  if (max_tx >= MAP_WIDTH)
    max_tx = MAP_WIDTH - 1;
  if (max_ty >= MAP_HEIGHT)
    max_ty = MAP_HEIGHT - 1;
  UBYTE max_cx = max_tx / CHUNK_SIZE;
  UBYTE max_cy = max_ty / CHUNK_SIZE;
  return cx >= min_cx && cx <= max_cx && cy >= min_cy && cy <= max_cy;
}

static void chunk_unload_lru(void)
{
  UBYTE best = 0xFF;
  UINT16 best_used = 0xFFFF;
  UBYTE cam_tx = camera_get_tile_x();
  UBYTE cam_ty = camera_get_tile_y();

  for (UBYTE i = 0; i < MAX_LOADED_CHUNKS; i++)
  {
    if (!loaded_chunks[i].loaded)
      continue;
    // Never evict chunks currently on screen
    if (chunk_intersects_camera(loaded_chunks[i].chunk_id, cam_tx, cam_ty))
      continue;
    if (loaded_chunks[i].last_used <= best_used)
    {
      best_used = loaded_chunks[i].last_used;
      best = i;
    }
  }

  // Fallback: if everything is pinned, evict the oldest anyway
  if (best == 0xFF)
  {
    best_used = 0xFFFF;
    for (UBYTE i = 0; i < MAX_LOADED_CHUNKS; i++)
    {
      if (!loaded_chunks[i].loaded)
        continue;
      if (loaded_chunks[i].last_used <= best_used)
      {
        best_used = loaded_chunks[i].last_used;
        best = i;
      }
    }
  }

  if (best == 0xFF)
    return;

  if (loaded_chunks[best].dirty)
    chunk_save_to_sram(loaded_chunks[best].chunk_id);

  chunk_slot_by_id[loaded_chunks[best].chunk_id] = 0xFF;
  loaded_chunks[best].loaded = FALSE;
  loaded_chunks[best].dirty = FALSE;
  if (loaded_chunk_count > 0)
    loaded_chunk_count--;
}

void chunk_system_init(void)
{
  loaded_chunk_count = 0;
  lru_tick = 0;
  for (UBYTE i = 0; i < SRAM_TOTAL_CHUNKS; i++)
    chunk_slot_by_id[i] = 0xFF;
  for (UBYTE i = 0; i < MAX_LOADED_CHUNKS; i++)
  {
    loaded_chunks[i].dirty = FALSE;
    loaded_chunks[i].loaded = FALSE;
    loaded_chunks[i].chunk_id = 0xFF;
    loaded_chunks[i].last_used = 0;
  }
}

UBYTE chunk_get_local_x(UBYTE world_tx) { return world_tx % CHUNK_SIZE; }
UBYTE chunk_get_local_y(UBYTE world_ty) { return world_ty % CHUNK_SIZE; }

UBYTE chunk_get_id_from_tile(UBYTE world_tx, UBYTE world_ty)
{
  UBYTE chunk_x = world_tx / CHUNK_SIZE;
  UBYTE chunk_y = world_ty / CHUNK_SIZE;
  return chunk_x + chunk_y * CHUNK_COUNT_X;
}

UINT16 chunk_get_sram_address(UBYTE chunk_id)
{
  return SRAM_CHUNKS_ADDR + (UINT16)chunk_id * SRAM_CHUNK_SIZE;
}

static cached_chunk_t *chunk_find_by_id(UBYTE chunk_id)
{
  UBYTE slot = chunk_slot_by_id[chunk_id];
  if (slot == 0xFF)
    return NULL;
  return &loaded_chunks[slot];
}

cached_chunk_t *chunk_ensure_loaded(UBYTE chunk_id)
{
  cached_chunk_t *chunk = chunk_find_by_id(chunk_id);
  if (chunk)
  {
    chunk_touch(chunk);
    return chunk;
  }

  if (loaded_chunk_count >= MAX_LOADED_CHUNKS)
    chunk_unload_lru();

  for (UBYTE i = 0; i < MAX_LOADED_CHUNKS; i++)
  {
    if (!loaded_chunks[i].loaded)
    {
      loaded_chunks[i].chunk_id = chunk_id;
      sram_read_block(chunk_get_sram_address(chunk_id),
                      (UBYTE *)&loaded_chunks[i].data, SRAM_CHUNK_SIZE);

      if (!chunk_data_is_valid(&loaded_chunks[i].data))
      {
        fill_chunk_from_template(chunk_id, &loaded_chunks[i].data);
        loaded_chunks[i].dirty = TRUE;
      }
      else
      {
        loaded_chunks[i].dirty = FALSE;
      }

      loaded_chunks[i].loaded = TRUE;
      chunk_slot_by_id[chunk_id] = i;
      chunk_touch(&loaded_chunks[i]);
      loaded_chunk_count++;
      return &loaded_chunks[i];
    }
  }
  return NULL;
}

void chunk_save_to_sram(UBYTE chunk_id)
{
  cached_chunk_t *chunk = chunk_find_by_id(chunk_id);
  if (chunk && chunk->dirty)
  {
    chunk_finalize_checksum(&chunk->data);
    sram_write_block(chunk_get_sram_address(chunk_id), (UBYTE *)&chunk->data,
                     SRAM_CHUNK_SIZE);
    chunk->dirty = FALSE;
  }
}

void chunk_flush_all(void)
{
  for (UBYTE i = 0; i < MAX_LOADED_CHUNKS; i++)
  {
    if (loaded_chunks[i].loaded && loaded_chunks[i].dirty)
      chunk_save_to_sram(loaded_chunks[i].chunk_id);
  }
}

UBYTE chunk_peek_tile(UBYTE world_tx, UBYTE world_ty)
{
  if (world_tx >= MAP_WIDTH || world_ty >= MAP_HEIGHT)
    return BG_WALL;

  UBYTE chunk_id = chunk_get_id_from_tile(world_tx, world_ty);
  cached_chunk_t *chunk = chunk_find_by_id(chunk_id);
  if (!chunk)
    return BG_EMPTY;

  return chunk->data.tiles[chunk_get_local_y(world_ty)][chunk_get_local_x(world_tx)];
}

UBYTE chunk_get_tile(UBYTE world_tx, UBYTE world_ty)
{
  if (world_tx >= MAP_WIDTH || world_ty >= MAP_HEIGHT)
    return BG_WALL;

  UBYTE chunk_id = chunk_get_id_from_tile(world_tx, world_ty);
  cached_chunk_t *chunk = chunk_ensure_loaded(chunk_id);
  if (!chunk)
    return BG_EMPTY;

  return chunk->data.tiles[chunk_get_local_y(world_ty)][chunk_get_local_x(world_tx)];
}

void chunk_set_tile(UBYTE world_tx, UBYTE world_ty, UBYTE tile_value)
{
  if (world_tx >= MAP_WIDTH || world_ty >= MAP_HEIGHT)
    return;

  UBYTE chunk_id = chunk_get_id_from_tile(world_tx, world_ty);
  cached_chunk_t *chunk = chunk_ensure_loaded(chunk_id);
  if (!chunk)
    return;

  chunk->data.tiles[chunk_get_local_y(world_ty)][chunk_get_local_x(world_tx)] = tile_value;
  chunk->dirty = TRUE;
}

void chunk_ensure_around_camera(UBYTE cam_tx, UBYTE cam_ty)
{
  UBYTE min_tx = cam_tx;
  UBYTE min_ty = cam_ty;
  UBYTE max_tx = cam_tx + SCREEN_TILE_WIDTH - 1;
  UBYTE max_ty = cam_ty + SCREEN_TILE_HEIGHT - 1;
  if (max_tx >= MAP_WIDTH)
    max_tx = MAP_WIDTH - 1;
  if (max_ty >= MAP_HEIGHT)
    max_ty = MAP_HEIGHT - 1;

  UBYTE min_cx = min_tx / CHUNK_SIZE;
  UBYTE min_cy = min_ty / CHUNK_SIZE;
  UBYTE max_cx = max_tx / CHUNK_SIZE;
  UBYTE max_cy = max_ty / CHUNK_SIZE;

  for (UBYTE cy = min_cy; cy <= max_cy; cy++)
  {
    for (UBYTE cx = min_cx; cx <= max_cx; cx++)
    {
      chunk_ensure_loaded(cx + cy * CHUNK_COUNT_X);
    }
  }
}

void chunk_system_update(void)
{
  chunk_ensure_around_camera(camera_get_tile_x(), camera_get_tile_y());
}

UBYTE world_sram_is_valid(void)
{
  UBYTE lo = sram_read_byte(SRAM_HEADER_ADDR);
  UBYTE hi = sram_read_byte(SRAM_HEADER_ADDR + 1);
  UBYTE ver = sram_read_byte(SRAM_HEADER_ADDR + 2);
  UINT16 magic = (UINT16)lo | ((UINT16)hi << 8);
  return (magic == SRAM_MAGIC && ver == SRAM_VERSION);
}

void world_sram_write_header(void)
{
  sram_write_byte(SRAM_HEADER_ADDR, (UBYTE)(SRAM_MAGIC & 0xFF));
  sram_write_byte(SRAM_HEADER_ADDR + 1, (UBYTE)((SRAM_MAGIC >> 8) & 0xFF));
  sram_write_byte(SRAM_HEADER_ADDR + 2, SRAM_VERSION);
  sram_write_byte(SRAM_HEADER_ADDR + 3, 1); // has_save
}

void world_seed_from_template(void)
{
  chunk_data_t chunk;
  for (UBYTE cy = 0; cy < CHUNK_COUNT_Y; cy++)
  {
    for (UBYTE cx = 0; cx < CHUNK_COUNT_X; cx++)
    {
      UBYTE chunk_id = cx + cy * CHUNK_COUNT_X;
      fill_chunk_from_template(chunk_id, &chunk);
      sram_write_block(chunk_get_sram_address(chunk_id), (UBYTE *)&chunk,
                       SRAM_CHUNK_SIZE);
    }
  }
}

void world_init(UBYTE force_new)
{
  chunk_system_init();

  if (force_new || !world_sram_is_valid())
  {
    world_seed_from_template();
    world_sram_write_header();
    sram_write_byte(SRAM_SCORE_ADDR, 0);
    sram_write_byte(SRAM_SCORE_ADDR + 1, 0);
  }

  chunk_ensure_loaded(0);
}
