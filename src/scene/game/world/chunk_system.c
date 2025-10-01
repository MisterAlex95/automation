#include "chunk_system.h"
#include "../../../assets/map.h"
#include "../core/sram_system.h"

static UBYTE loaded_chunk_count = 0;
static cached_chunk_t loaded_chunks[MAX_LOADED_CHUNKS];

void chunk_system_init(void) {
  loaded_chunk_count = 0;
  for (UBYTE i = 0; i < MAX_LOADED_CHUNKS; i++) {
    loaded_chunks[i].dirty = FALSE;
    loaded_chunks[i].loaded = FALSE;
  }
}

UBYTE chunk_get_local_x(UBYTE world_x) { return world_x % CHUNK_SIZE; }
UBYTE chunk_get_local_y(UBYTE world_y) { return world_y % CHUNK_SIZE; }

cached_chunk_t *chunk_find_by_id(UBYTE chunk_id) {
  for (UBYTE i = 0; i < MAX_LOADED_CHUNKS; i++) {
    if (loaded_chunks[i].chunk_id == chunk_id) {
      return &loaded_chunks[i];
    }
  }
  return NULL;
}

void chunk_load_from_sram(UBYTE chunk_id) {
  if (loaded_chunk_count >= MAX_LOADED_CHUNKS) {
    chunk_unload_oldest();
  }

  for (UBYTE i = 0; i < MAX_LOADED_CHUNKS; i++) {
    if (!loaded_chunks[i].loaded) {
      loaded_chunks[i].chunk_id = chunk_id;
      sram_read_block(chunk_get_sram_address(chunk_id),
                      (UBYTE *)&loaded_chunks[i].data, SRAM_CHUNK_SIZE);

      loaded_chunks[i].loaded = TRUE;
      loaded_chunks[i].dirty = FALSE;

      loaded_chunk_count++;
      break;
    }
  }
}

void chunk_save_to_sram(UBYTE chunk_id) {
  cached_chunk_t *chunk = chunk_find_by_id(chunk_id);
  if (chunk && chunk->dirty) {
    sram_write_block(chunk_get_sram_address(chunk_id), (UBYTE *)&chunk->data,
                     SRAM_CHUNK_SIZE);
    chunk->dirty = FALSE;
  }
}

UINT16 chunk_get_sram_address(UBYTE chunk_id) {
  return chunk_id * SRAM_CHUNK_SIZE;
}

chunk_t *chunk_get_at_position(UBYTE world_x, UBYTE world_y) {
  UBYTE chunk_x = world_x / CHUNK_SIZE;
  UBYTE chunk_y = world_y / CHUNK_SIZE;

  if (chunk_x >= CHUNK_COUNT_X || chunk_y >= CHUNK_COUNT_Y) {
    return NULL;
  }

  UBYTE chunk_id = chunk_get_id(world_x, world_y);
  cached_chunk_t *chunk = chunk_find_by_id(chunk_id);

  if (chunk == NULL) {
    chunk_load_from_sram(chunk_id);
    chunk = chunk_find_by_id(chunk_id);
  }

  return chunk ? &chunk->data : NULL;
}

UBYTE chunk_get_id(UBYTE world_x, UBYTE world_y) {
  return (world_x / CHUNK_SIZE) + (world_y / CHUNK_SIZE) * CHUNK_COUNT_X;
}

void chunk_unload_oldest(void) {
  for (UBYTE i = 0; i < MAX_LOADED_CHUNKS; i++) {
    if (loaded_chunks[i].loaded) {
      if (loaded_chunks[i].dirty) {
        chunk_save_to_sram(loaded_chunks[i].chunk_id);
      }
      loaded_chunks[i].loaded = FALSE;
      loaded_chunk_count--;
      break;
    }
  }
}

void chunk_system_update(void) {}
